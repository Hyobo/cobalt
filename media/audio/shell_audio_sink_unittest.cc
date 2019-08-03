/*
 * Copyright 2012 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "media/audio/shell_audio_sink.h"

#include <algorithm>

#include "media/audio/mock_shell_audio_streamer.h"
#include "media/base/mock_filters.h"
#include "media/base/shell_filter_graph_log.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace {

using namespace testing;

bool operator ==(const media::AudioParameters& params1,
                 const media::AudioParameters& params2) {
  return params1.channels() == params2.channels() &&
      params1.bits_per_sample() == params2.bits_per_sample() &&
      params1.sample_rate() == params2.sample_rate();
}

void InterleavedFill(size_t frames_per_channel, int channels,
                     int bytes_per_sample, uint8* data, uint8* fill_byte) {
  while (frames_per_channel) {
    for (int i = 0; i < channels; ++i) {
      for (int j = 0; j < bytes_per_sample; ++j) {
        *data = *fill_byte + j;
        ++data;
      }
    }
    *fill_byte += bytes_per_sample;
    --frames_per_channel;
  }
}

void InterleavedVerify(size_t frames_per_channel, int channels,
                       int bytes_per_sample, const uint8* data,
                       uint8* fill_byte) {
  while (frames_per_channel) {
    for (int i = 0; i < channels; ++i) {
      for (int j = 0; j < bytes_per_sample; ++j) {
        ASSERT_EQ(*data, static_cast<uint8>(*fill_byte + j));
        ++data;
      }
    }
    *fill_byte += bytes_per_sample;
    --frames_per_channel;
  }
}

class MockRenderCallback : public media::AudioRendererSink::RenderCallback {
 public:
  MockRenderCallback() {}

  MOCK_METHOD2(Render, int (media::AudioBus*, int));
  MOCK_METHOD3(RenderIO, void (media::AudioBus*, media::AudioBus*, int));
  MOCK_METHOD0(OnRenderError, void ());
  MOCK_METHOD0(SinkFull, void());

  MOCK_METHOD0(SinkUnderflow, void ());

  DISALLOW_COPY_AND_ASSIGN(MockRenderCallback);
};

class ShellAudioSinkTest : public testing::Test {
 public:
  ShellAudioSinkTest() {
    media::ShellBufferFactory::Initialize();
  }

  virtual ~ShellAudioSinkTest() {
    media::ShellBufferFactory::Terminate();
  }

  void Setup(const media::ShellAudioStreamer::Config& config) {
    render_byte_ = 0;
    consumption_byte_ = 0;
    render_bytes_num_ = 0;
    consumption_bytes_num_ = 0;
    render_frames_per_channel_ = 0;
    consumption_frames_per_channel_ = 0;

    sink_ = media::ShellAudioSink::Create(&streamer_);
    filter_graph_log_ = new media::ShellFilterGraphLog;
    EXPECT_CALL(streamer_, GetConfig()).WillRepeatedly(Return(config));
    EXPECT_CALL(streamer_,
                HasStream(sink_.get())).WillRepeatedly(Return(false));
    EXPECT_CALL(render_callback_, Render(_, _)).WillRepeatedly(Return(0));
    EXPECT_CALL(render_callback_, SinkFull()).Times(AnyNumber());
    EXPECT_CALL(render_callback_, SinkUnderflow()).Times(AnyNumber());
  }

  void FillAudioBus(int frames_per_channel, media::AudioBus* audio_bus) {
    media::ShellAudioStreamer::Config config = streamer_.GetConfig();
    media::AudioParameters params = sink_->GetAudioParameters();
    int bytes_per_channel = frames_per_channel * params.bits_per_sample() / 8;
    int channels = params.channels();
    if (config.decode_mono_as_stereo && channels == 1)
      channels = 2;
    if (config.interleaved) {
      bytes_per_channel *= channels;
    }
    ASSERT_LE(bytes_per_channel, audio_bus->frames() * sizeof(float));

    if (config.interleaved) {
      ASSERT_EQ(audio_bus->channels(), 1);
      InterleavedFill(frames_per_channel, channels,
                      params.bits_per_sample() / 8,
                      reinterpret_cast<uint8*>(audio_bus->channel(0)),
                      &render_byte_);
    } else {
      ASSERT_EQ(audio_bus->channels(), channels);
      uint8 render_byte;
      for (int i = 0; i < channels; ++i) {
        render_byte = render_byte_;
        InterleavedFill(frames_per_channel, 1,
                        params.bits_per_sample() / 8,
                        reinterpret_cast<uint8*>(audio_bus->channel(i)),
                        &render_byte);
      }
      render_byte_ = render_byte;
    }

    render_bytes_num_ += channels * bytes_per_channel;
    render_frames_per_channel_ += frames_per_channel;
  }

  void Consume(int frames_per_channel) {
    media::ShellAudioStreamer::Config config = streamer_.GetConfig();
    media::AudioParameters params = sink_->GetAudioParameters();
    media::AudioSinkSettings settings;
    media::AudioBus* audio_bus = sink_->GetAudioBus();
    int bytes_per_channel = frames_per_channel * params.bits_per_sample() / 8;

    settings.Reset(config, params);
    if (config.interleaved) {
      bytes_per_channel *= settings.channels();
    }
    ASSERT_LE(bytes_per_channel, audio_bus->frames() * sizeof(float));

    uint32_t offset_in_frame, total_frames;
    EXPECT_CALL(render_callback_, Render(_, _)).WillOnce(Return(0));
    sink_->PullFrames(&offset_in_frame, &total_frames);

    EXPECT_LE(frames_per_channel, total_frames);

    int frames_to_request =
        std::min<int>(frames_per_channel,
                      settings.per_channel_frames(audio_bus) - offset_in_frame);
    if (config.interleaved) {
      ASSERT_EQ(audio_bus->channels(), 1);
      uint8* data = reinterpret_cast<uint8*>(audio_bus->channel(0)) +
          offset_in_frame * params.bits_per_sample() / 8 * settings.channels();
      InterleavedVerify(frames_to_request, settings.channels(),
                        params.bits_per_sample() / 8,
                        data, &consumption_byte_);
    } else {
      ASSERT_EQ(audio_bus->channels(), settings.channels());
      uint8 consumption_byte;
      for (int i = 0; i < settings.channels(); ++i) {
        consumption_byte = consumption_byte_;
        uint8* data = reinterpret_cast<uint8*>(audio_bus->channel(i)) +
            offset_in_frame * params.bits_per_sample() / 8;
        InterleavedVerify(frames_to_request, 1,
                          params.bits_per_sample() / 8,
                          data, &consumption_byte);
      }
      consumption_byte_ = consumption_byte;
    }

    frames_to_request = frames_per_channel - frames_to_request;
    if (frames_to_request != 0) {
      if (config.interleaved) {
        ASSERT_EQ(audio_bus->channels(), 1);
        uint8* data = reinterpret_cast<uint8*>(audio_bus->channel(0));
        InterleavedVerify(frames_to_request, settings.channels(),
                          params.bits_per_sample() / 8,
                          data, &consumption_byte_);
      } else {
        ASSERT_EQ(audio_bus->channels(), settings.channels());
        uint8 consumption_byte;
        for (int i = 0; i < settings.channels(); ++i) {
          consumption_byte = consumption_byte_;
          uint8* data = reinterpret_cast<uint8*>(audio_bus->channel(i));
          InterleavedVerify(frames_to_request, 1,
                            params.bits_per_sample() / 8,
                            data, &consumption_byte);
        }
        consumption_byte_ = consumption_byte;
      }
    }

    sink_->ConsumeFrames(frames_per_channel);

    consumption_bytes_num_ += settings.channels() * bytes_per_channel;
    consumption_frames_per_channel_ += frames_per_channel;
  }

  bool AllConsumed() {
    uint32_t offset_in_frame, total_frames;
    EXPECT_CALL(render_callback_, Render(_, _))
        .Times(AtLeast(0)).WillRepeatedly(Return(0));
    sink_->PullFrames(&offset_in_frame, &total_frames);

    return total_frames == 0 && render_byte_ == consumption_byte_ &&
        render_bytes_num_ == consumption_bytes_num_ &&
        render_frames_per_channel_ == consumption_frames_per_channel_;
  }

  // ==== Test Fixture Members
  media::MockShellAudioStreamer streamer_;
  MockRenderCallback render_callback_;
  scoped_refptr<media::ShellAudioSink> sink_;
  scoped_refptr<media::ShellFilterGraphLog> filter_graph_log_;

  uint8 render_byte_;
  uint8 consumption_byte_;
  int render_bytes_num_;
  int consumption_bytes_num_;
  int render_frames_per_channel_;
  int consumption_frames_per_channel_;
};

// Verify the frame count of audio_bus
ACTION_P3(VerifyAudioBusFrameCount, config, init_params, frames_per_channel) {
  media::AudioBus* audio_bus = arg0;
  int bytes_per_channel = frames_per_channel *
      init_params.bits_per_sample() / 8;
  if (config.interleaved) {
    int channels = init_params.channels();
    if (config.decode_mono_as_stereo && channels == 1)
      channels = 2;
    bytes_per_channel *= channels;
  }
  EXPECT_EQ(bytes_per_channel, audio_bus->frames() * sizeof(float));
  return 0;
}

// Verify the frame count of audio_bus
ACTION_P2(RenderAudioBus, frames_per_channel, sink_test) {
  media::AudioBus* audio_bus = arg0;
  sink_test->FillAudioBus(frames_per_channel, audio_bus);
  return frames_per_channel;
}

TEST_F(ShellAudioSinkTest, Prerequisites) {
  uint8 data[48000] = {0};
  uint8 render_byte = 0, consume_byte = 0;
  uint8 verify_data[] = {0x00, 0x01, 0x02, 0x00, 0x01, 0x02, 0x00, 0x01, 0x02,
      0x03, 0x04, 0x05, 0x03, 0x04, 0x05, 0x03, 0x04, 0x05};
  InterleavedFill(2, 3, 3, data, &render_byte);
  EXPECT_EQ(memcmp(verify_data, data, 9), 0);
  EXPECT_EQ(memcmp(data + 18, data + 19, 1024), 0);

  for (size_t frames_per_channel = 1; frames_per_channel < 301;
       frames_per_channel += 3) {
    for (int channels = 1; channels < 5; ++channels) {
      for (int bytes_per_sample = 1; bytes_per_sample < 5;
           ++bytes_per_sample) {
        render_byte = consume_byte = 0;
        InterleavedFill(frames_per_channel, channels, bytes_per_sample,
                        data, &render_byte);
        InterleavedVerify(frames_per_channel, channels, bytes_per_sample,
                          data, &consume_byte);
	ASSERT_EQ(render_byte, consume_byte);
      }
    }
  }
}

TEST_F(ShellAudioSinkTest, Initialize) {
  media::ShellAudioStreamer::Config config;

  config.renderer_request_frames = 1024;
  config.initial_rebuffering_frames_per_channel = 2048;
  config.max_frames_per_channel = 8192;
  config.initial_frames_per_channel = 4096;

  // 4 configurations with different interleaved and decode_mono_as_stereo
  for (int i = 0; i < 4; ++i) {
    config.interleaved = i / 2 != 0;
    config.decode_mono_as_stereo = i % 2 != 0;

    for (media::ChannelLayout layout = media::CHANNEL_LAYOUT_MONO;
         layout != media::CHANNEL_LAYOUT_MAX;
         layout = static_cast<media::ChannelLayout>(layout + 1)) {
      for (int bytes_per_sample = 2; bytes_per_sample < 5;
           bytes_per_sample *= 2) {
        Setup(config);
        EXPECT_TRUE(!sink_->GetAudioBus());
        media::AudioParameters init_params = media::AudioParameters(
            media::AudioParameters::AUDIO_PCM_LOW_LATENCY, layout,
            48000, bytes_per_sample * 8, 1024);
        sink_->Initialize(init_params, &render_callback_,
                          filter_graph_log_.get());

        EXPECT_TRUE(sink_->PauseRequested());
        EXPECT_TRUE(sink_->GetAudioBus());

        media::AudioBus* audio_bus = sink_->GetAudioBus();
        media::AudioParameters params = sink_->GetAudioParameters();
        int expected_channels = init_params.channels();
        if (expected_channels == 1 && config.decode_mono_as_stereo)
          expected_channels = 2;
        if (config.interleaved) {
          EXPECT_EQ(audio_bus->channels(), 1);
          EXPECT_EQ(audio_bus->frames(),
              config.initial_frames_per_channel * expected_channels *
              bytes_per_sample / sizeof(float));
          EXPECT_EQ(params.channels(), init_params.channels());
        } else {
          EXPECT_EQ(audio_bus->channels(), expected_channels);
          EXPECT_EQ(audio_bus->frames(), config.initial_frames_per_channel *
              bytes_per_sample / sizeof(float));
          EXPECT_EQ(params.channels(), init_params.channels());
        }

        EXPECT_EQ(params.bits_per_sample(), init_params.bits_per_sample());
        EXPECT_EQ(params.sample_rate(), init_params.sample_rate());
      }
    }
  }
}

TEST_F(ShellAudioSinkTest, StartAndStop) {
  media::ShellAudioStreamer::Config config;

  config.interleaved = true;
  config.decode_mono_as_stereo = true;
  config.renderer_request_frames = 1024;
  config.initial_rebuffering_frames_per_channel = 2048;
  config.max_frames_per_channel = 8192;
  config.initial_frames_per_channel = 4096;

  media::AudioParameters init_params = media::AudioParameters(
      media::AudioParameters::AUDIO_PCM_LOW_LATENCY,
      media::CHANNEL_LAYOUT_MONO, 48000, 16, 1024);

  Setup(config);

  sink_->Initialize(init_params, &render_callback_, filter_graph_log_.get());

  InSequence seq;
  EXPECT_CALL(streamer_, HasStream(sink_.get())).WillRepeatedly(Return(false));
  EXPECT_CALL(streamer_, AddStream(sink_.get())).WillOnce(Return(true));
  EXPECT_CALL(streamer_, HasStream(sink_.get())).WillRepeatedly(Return(true));
  sink_->Start();
  EXPECT_TRUE(sink_->PauseRequested());
  EXPECT_CALL(streamer_, RemoveStream(sink_.get())).WillOnce(Return());
  EXPECT_CALL(streamer_, HasStream(sink_.get())).WillRepeatedly(Return(false));
  sink_->Stop();
  EXPECT_TRUE(sink_->PauseRequested());
}

TEST_F(ShellAudioSinkTest, RenderNoFrames) {
  media::ShellAudioStreamer::Config config;

  config.interleaved = true;
  config.decode_mono_as_stereo = true;
  config.renderer_request_frames = 1024;
  config.initial_rebuffering_frames_per_channel = 2048;
  config.max_frames_per_channel = 8192;
  config.initial_frames_per_channel = 4096;

  Setup(config);

  media::AudioParameters init_params = media::AudioParameters(
      media::AudioParameters::AUDIO_PCM_LOW_LATENCY,
      media::CHANNEL_LAYOUT_MONO, 48000, 16, 1024);

  sink_->Initialize(init_params, &render_callback_, filter_graph_log_.get());

  InSequence seq;
  EXPECT_CALL(streamer_, HasStream(sink_.get())).WillRepeatedly(Return(false));
  EXPECT_CALL(streamer_, AddStream(sink_.get())).WillOnce(Return(true));
  EXPECT_CALL(streamer_, HasStream(sink_.get())).WillRepeatedly(Return(true));
  sink_->Start();

  EXPECT_FALSE(sink_->PullFrames(NULL, NULL));
  uint32_t offset_in_frame, total_frames;
  EXPECT_FALSE(sink_->PullFrames(&offset_in_frame, &total_frames));

  EXPECT_CALL(streamer_, RemoveStream(sink_.get())).WillOnce(Return());
  EXPECT_CALL(streamer_, HasStream(sink_.get())).WillRepeatedly(Return(false));
  sink_->Stop();
}

TEST_F(ShellAudioSinkTest, RenderFrames) {
  media::ShellAudioStreamer::Config config;

  config.renderer_request_frames = 1024;
  config.initial_rebuffering_frames_per_channel = 2048;
  config.max_frames_per_channel = 8192;
  config.initial_frames_per_channel = 4096;

  for (int i = 0; i < 4; ++i) {
    config.interleaved = i / 2 != 0;
    config.decode_mono_as_stereo = i % 2 != 0;
    Setup(config);

    media::AudioParameters init_params = media::AudioParameters(
        media::AudioParameters::AUDIO_PCM_LOW_LATENCY,
        media::CHANNEL_LAYOUT_MONO, 48000, 16, 1024);

    sink_->Initialize(init_params, &render_callback_, filter_graph_log_.get());

    InSequence seq;
    EXPECT_CALL(streamer_, HasStream(sink_.get())).
        WillRepeatedly(Return(false));
    EXPECT_CALL(streamer_, AddStream(sink_.get())).WillOnce(Return(true));
    EXPECT_CALL(streamer_, HasStream(sink_.get())).
        WillRepeatedly(Return(true));
    sink_->Start();

    EXPECT_CALL(render_callback_, Render(_, _))
        .WillOnce(RenderAudioBus(16, this));
    EXPECT_FALSE(sink_->PullFrames(NULL, NULL));

    uint32_t offset_in_frame, total_frames;
    EXPECT_CALL(render_callback_, Render(_, _)).WillOnce(Return(0));
    EXPECT_FALSE(sink_->PullFrames(&offset_in_frame, &total_frames));
    EXPECT_EQ(offset_in_frame, 0);
    EXPECT_EQ(total_frames, 16);

    EXPECT_CALL(render_callback_, Render(_, _))
        .WillOnce(RenderAudioBus(8, this));
    EXPECT_FALSE(sink_->PullFrames(&offset_in_frame, &total_frames));
    EXPECT_EQ(offset_in_frame, 0);
    EXPECT_EQ(total_frames, 24);

    Consume(8);

    EXPECT_CALL(render_callback_, Render(_, _)).WillOnce(Return(0));
    EXPECT_FALSE(sink_->PullFrames(&offset_in_frame, &total_frames));
    EXPECT_EQ(offset_in_frame, 8);
    EXPECT_EQ(total_frames, 16);

    Consume(16);

    EXPECT_TRUE(AllConsumed());

    EXPECT_CALL(streamer_, HasStream(sink_.get()))
        .WillRepeatedly(Return(true));
    EXPECT_CALL(streamer_, RemoveStream(sink_.get()))
        .WillOnce(Return());
    EXPECT_CALL(streamer_, HasStream(sink_.get()))
        .WillRepeatedly(Return(false));
    sink_->Stop();
  }
}

TEST_F(ShellAudioSinkTest, RenderRequestSizeAkaAudioBusFrames) {
  media::ShellAudioStreamer::Config config;

  config.renderer_request_frames = 64;
  config.initial_rebuffering_frames_per_channel = 128;
  config.max_frames_per_channel = 128;
  config.initial_frames_per_channel = 128;

  for (int i = 0; i < 4; ++i) {
    config.interleaved = i / 2 != 0;
    config.decode_mono_as_stereo = i % 2 != 0;
    Setup(config);

    media::AudioParameters init_params = media::AudioParameters(
        media::AudioParameters::AUDIO_PCM_LOW_LATENCY,
        media::CHANNEL_LAYOUT_MONO, 48000, 16, 1024);

    sink_->Initialize(init_params, &render_callback_, filter_graph_log_.get());

    InSequence seq;
    EXPECT_CALL(streamer_, HasStream(sink_.get())).
        WillRepeatedly(Return(false));
    EXPECT_CALL(streamer_, AddStream(sink_.get())).WillOnce(Return(true));
    EXPECT_CALL(streamer_, HasStream(sink_.get())).
        WillRepeatedly(Return(true));
    sink_->Start();

    for (int i = 0; i < 10; ++i) {
      // Try to get 64 frames but don't give it any data
      EXPECT_CALL(render_callback_, Render(_, _))
          .WillOnce(VerifyAudioBusFrameCount(config, init_params,
                                             config.renderer_request_frames));
      EXPECT_FALSE(sink_->PullFrames(NULL, NULL));

      // Ok, now give it 64 frames
      EXPECT_CALL(render_callback_, Render(_, _))
          .WillOnce(RenderAudioBus(64, this));
      EXPECT_FALSE(sink_->PullFrames(NULL, NULL));

      // Try to get another 64 frames but don't give it any data
      EXPECT_CALL(render_callback_, Render(_, _))
          .WillOnce(VerifyAudioBusFrameCount(config, init_params,
                                             config.renderer_request_frames));
      EXPECT_FALSE(sink_->PullFrames(NULL, NULL));

      // Ok, now give it 48 frames
      EXPECT_CALL(render_callback_, Render(_, _))
          .WillOnce(RenderAudioBus(48, this));
      EXPECT_FALSE(sink_->PullFrames(NULL, NULL));

      // Now it only has room for 16 frames, which is less than the minimum
      // request size, so there shouldn't be any call to Render.
      EXPECT_CALL(render_callback_, Render(_, _)).Times(0);
      EXPECT_FALSE(sink_->PullFrames(NULL, NULL));

      // Consume 64 frames, leave 80 frames space but only 16 are continuous
      Consume(64);

      // It still only has room for 16 continuous frames, don't give it any
      EXPECT_CALL(render_callback_, Render(_, _))
          .WillOnce(VerifyAudioBusFrameCount(config, init_params, 16));
      EXPECT_FALSE(sink_->PullFrames(NULL, NULL));

      // Ok, now give it 16 frames
      EXPECT_CALL(render_callback_, Render(_, _))
          .WillOnce(RenderAudioBus(16, this));
      EXPECT_FALSE(sink_->PullFrames(NULL, NULL));

      // Now it has room for another 64 frames, don't give it
      EXPECT_CALL(render_callback_, Render(_, _))
          .WillOnce(VerifyAudioBusFrameCount(config, init_params, 64));
      EXPECT_FALSE(sink_->PullFrames(NULL, NULL));

      // Ok, now give it 64 frames
      EXPECT_CALL(render_callback_, Render(_, _))
          .WillOnce(RenderAudioBus(64, this));
      EXPECT_FALSE(sink_->PullFrames(NULL, NULL));

      // Consume 128 frames
      Consume(128);

      // Give it another 64 and then consume 64 to ensure we can get into the
      // next iteration of the loop with empty buffer
      EXPECT_CALL(render_callback_, Render(_, _))
          .WillOnce(RenderAudioBus(64, this));
      EXPECT_FALSE(sink_->PullFrames(NULL, NULL));
      Consume(64);

      EXPECT_TRUE(AllConsumed());
    }

    EXPECT_CALL(streamer_, HasStream(sink_.get()))
        .WillRepeatedly(Return(true));
    EXPECT_CALL(streamer_, RemoveStream(sink_.get()))
        .WillOnce(Return());
    EXPECT_CALL(streamer_, HasStream(sink_.get()))
        .WillRepeatedly(Return(false));
    sink_->Stop();
  }
}

TEST_F(ShellAudioSinkTest, ResumeAfterUnderflow) {
  media::ShellAudioStreamer::Config config;

  config.renderer_request_frames = 64;
  config.initial_rebuffering_frames_per_channel = 128;
  config.max_frames_per_channel = 256;
  config.initial_frames_per_channel = 128;

  for (int i = 0; i < 4; ++i) {
    config.interleaved = i / 2 != 0;
    config.decode_mono_as_stereo = i % 2 != 0;
    Setup(config);

    media::AudioParameters init_params = media::AudioParameters(
        media::AudioParameters::AUDIO_PCM_LOW_LATENCY,
        media::CHANNEL_LAYOUT_MONO, 48000, 16, 1024);

    sink_->Initialize(init_params, &render_callback_, filter_graph_log_.get());

    InSequence seq;
    EXPECT_CALL(streamer_, HasStream(sink_.get())).
        WillRepeatedly(Return(false));
    EXPECT_CALL(streamer_, AddStream(sink_.get())).WillOnce(Return(true));
    EXPECT_CALL(streamer_, HasStream(sink_.get())).
        WillRepeatedly(Return(true));
    sink_->Start();

    // Render 64 frames
    EXPECT_CALL(render_callback_, Render(_, _))
        .WillOnce(RenderAudioBus(64, this));
    EXPECT_FALSE(sink_->PullFrames(NULL, NULL));

    // Render another 64 frames
    EXPECT_CALL(render_callback_, Render(_, _))
        .WillOnce(RenderAudioBus(64, this));
    EXPECT_FALSE(sink_->PullFrames(NULL, NULL));

    // Consume 112 frames, leave 16 frames left
    Consume(112);

    // Render another 16 frames
    EXPECT_CALL(render_callback_, Render(_, _))
        .WillOnce(RenderAudioBus(16, this));
    EXPECT_FALSE(sink_->PullFrames(NULL, NULL));

    // Now we have 32 frames in the buffer, 16 frames is the last 16 frames
    // of a 64 frames render, another 16 frames is from a 16 frames render.
    // Now do a ResumeAfterUnderflow to double the buffer
    int frames = sink_->GetAudioBus()->frames();
    sink_->ResumeAfterUnderflow(false);
    EXPECT_EQ(sink_->GetAudioBus()->frames(), frames);
    sink_->ResumeAfterUnderflow(true);
    EXPECT_EQ(sink_->GetAudioBus()->frames(), frames * 2);

    Consume(32);

    EXPECT_TRUE(AllConsumed());

    EXPECT_CALL(streamer_, HasStream(sink_.get()))
        .WillRepeatedly(Return(true));
    EXPECT_CALL(streamer_, RemoveStream(sink_.get()))
        .WillOnce(Return());
    EXPECT_CALL(streamer_, HasStream(sink_.get()))
        .WillRepeatedly(Return(false));
    sink_->Stop();
  }
}

}  // namespace
