// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "net/spdy/buffered_spdy_framer.h"

#include "net/spdy/spdy_test_util_spdy3.h"
#include "testing/platform_test.h"

using namespace net::test_spdy3;

namespace spdy {

namespace {

class TestBufferedSpdyVisitor : public BufferedSpdyFramerVisitorInterface {
 public:
  TestBufferedSpdyVisitor()
    : buffered_spdy_framer_(3),
      error_count_(0),
      setting_count_(0),
      syn_frame_count_(0),
      syn_reply_frame_count_(0),
      headers_frame_count_(0),
      header_stream_id_(-1) {
  }

  void OnError(int error_code) {
    LOG(INFO) << "SpdyFramer Error: " << error_code;
    error_count_++;
  }

  void OnStreamError(spdy::SpdyStreamId stream_id,
                     const std::string& description) {
    LOG(INFO) << "SpdyFramer Error on stream: " << stream_id  << " "
              << description;
    error_count_++;
  }

  void OnSynStream(const SpdySynStreamControlFrame& frame,
             const linked_ptr<SpdyHeaderBlock>& headers) {
    header_stream_id_ = frame.stream_id();
    EXPECT_NE(header_stream_id_, SpdyFramer::kInvalidStream);
    syn_frame_count_++;
    headers_ = *headers;
  }

  void OnSynReply(const SpdySynReplyControlFrame& frame,
                  const linked_ptr<SpdyHeaderBlock>& headers) {
    header_stream_id_ = frame.stream_id();
    EXPECT_NE(header_stream_id_, SpdyFramer::kInvalidStream);
    syn_reply_frame_count_++;
    headers_ = *headers;
  }

  void OnHeaders(const SpdyHeadersControlFrame& frame,
                 const linked_ptr<SpdyHeaderBlock>& headers) {
    header_stream_id_ = frame.stream_id();
    EXPECT_NE(header_stream_id_, SpdyFramer::kInvalidStream);
    headers_frame_count_++;
    headers_ = *headers;
  }

  void OnStreamFrameData(SpdyStreamId stream_id,
                         const char* data,
                         size_t len) {
    LOG(FATAL) << "Unexpected OnStreamFrameData call.";
  }

  void OnSetting(SpdySettingsIds id, uint8 flags, uint32 value) {
    setting_count_++;
  }

  bool OnCredentialFrameData(const char*, size_t) {
    LOG(FATAL) << "Unexpected OnCredentialFrameData call.";
    return false;
  }

  void OnDataFrameHeader(const SpdyDataFrame* frame) {
    LOG(FATAL) << "Unexpected OnDataFrameHeader call.";
  }

  void OnControl(const SpdyControlFrame* frame) {
    uint32 type = frame->type();
    switch (type) {
      case SYN_STREAM:
      case SYN_REPLY:
      case HEADERS:
        header_stream_id_ = SpdyFramer::GetControlFrameStreamId(frame);
        EXPECT_NE(header_stream_id_, SpdyFramer::kInvalidStream);
        buffered_spdy_framer_.OnControl(frame);
        break;
      default:
        LOG(FATAL) << "Unexpected frame type." << type;
    }
  }

  void OnRstStream(const spdy::SpdyRstStreamControlFrame& frame) {}
  void OnGoAway(const spdy::SpdyGoAwayControlFrame& frame) {}
  void OnPing(const spdy::SpdyPingControlFrame& frame) {}
  void OnWindowUpdate(const spdy::SpdyWindowUpdateControlFrame& frame) {}
  void OnCredential(const spdy::SpdyCredentialControlFrame& frame) {}

  // Convenience function which runs a framer simulation with particular input.
  void SimulateInFramer(const unsigned char* input, size_t size) {
    buffered_spdy_framer_.set_visitor(this);
    size_t input_remaining = size;
    const char* input_ptr = reinterpret_cast<const char*>(input);
    while (input_remaining > 0 &&
           buffered_spdy_framer_.error_code() == SpdyFramer::SPDY_NO_ERROR) {
      // To make the tests more interesting, we feed random (amd small) chunks
      // into the framer.  This simulates getting strange-sized reads from
      // the socket.
      const size_t kMaxReadSize = 32;
      size_t bytes_read =
          (rand() % std::min(input_remaining, kMaxReadSize)) + 1;
      size_t bytes_processed =
          buffered_spdy_framer_.ProcessInput(input_ptr, bytes_read);
      input_remaining -= bytes_processed;
      input_ptr += bytes_processed;
      if (buffered_spdy_framer_.state() == SpdyFramer::SPDY_DONE)
        buffered_spdy_framer_.Reset();
    }
  }

  BufferedSpdyFramer buffered_spdy_framer_;

  // Counters from the visitor callbacks.
  int error_count_;
  int setting_count_;
  int syn_frame_count_;
  int syn_reply_frame_count_;
  int headers_frame_count_;

  // Header block streaming state:
  SpdyStreamId header_stream_id_;

  // Headers from OnSyn, OnSynReply and OnHeaders for verification.
  SpdyHeaderBlock headers_;
};

}  // namespace

class BufferedSpdyFramerSpdy3Test : public PlatformTest {
 protected:
  // Returns true if the two header blocks have equivalent content.
  bool CompareHeaderBlocks(const SpdyHeaderBlock* expected,
                           const SpdyHeaderBlock* actual) {
    if (expected->size() != actual->size()) {
      LOG(ERROR) << "Expected " << expected->size() << " headers; actually got "
                 << actual->size() << ".";
      return false;
    }
    for (SpdyHeaderBlock::const_iterator it = expected->begin();
         it != expected->end();
         ++it) {
      SpdyHeaderBlock::const_iterator it2 = actual->find(it->first);
      if (it2 == actual->end()) {
        LOG(ERROR) << "Expected header name '" << it->first << "'.";
        return false;
      }
      if (it->second.compare(it2->second) != 0) {
        LOG(ERROR) << "Expected header named '" << it->first
                   << "' to have a value of '" << it->second
                   << "'. The actual value received was '" << it2->second
                   << "'.";
        return false;
      }
    }
    return true;
  }

 private:
  SpdyTestStateHelper spdy_state_;
};

TEST_F(BufferedSpdyFramerSpdy3Test, OnSetting) {
  SpdyFramer framer(3);
  SpdySettings settings;
  settings.push_back(SpdySetting(SettingsFlagsAndId(0, 1), 0x00000002));
  settings.push_back(SpdySetting(SettingsFlagsAndId(0, 1), 0x00000003));

  scoped_ptr<SpdyFrame> control_frame(framer.CreateSettings(settings));
  TestBufferedSpdyVisitor visitor;

  visitor.SimulateInFramer(
      reinterpret_cast<unsigned char*>(control_frame->data()),
      control_frame->length() + SpdyControlFrame::kHeaderSize);
  EXPECT_EQ(1, visitor.error_count_);
  EXPECT_EQ(1, visitor.setting_count_);
}

TEST_F(BufferedSpdyFramerSpdy3Test, ReadSynStreamHeaderBlock) {
  SpdyHeaderBlock headers;
  headers["aa"] = "vv";
  headers["bb"] = "ww";
  BufferedSpdyFramer framer(3);
  scoped_ptr<SpdySynStreamControlFrame> control_frame(
      framer.CreateSynStream(1,                        // stream_id
                             0,                        // associated_stream_id
                             1,                        // priority
                             CONTROL_FLAG_NONE,
                             true,                     // compress
                             &headers));
  EXPECT_TRUE(control_frame.get() != NULL);

  TestBufferedSpdyVisitor visitor;
  visitor.SimulateInFramer(
      reinterpret_cast<unsigned char*>(control_frame.get()->data()),
      control_frame.get()->length() + SpdyControlFrame::kHeaderSize);
  EXPECT_EQ(0, visitor.error_count_);
  EXPECT_EQ(1, visitor.syn_frame_count_);
  EXPECT_EQ(0, visitor.syn_reply_frame_count_);
  EXPECT_EQ(0, visitor.headers_frame_count_);
  EXPECT_TRUE(CompareHeaderBlocks(&headers, &visitor.headers_));
}

TEST_F(BufferedSpdyFramerSpdy3Test, ReadSynReplyHeaderBlock) {
  SpdyHeaderBlock headers;
  headers["alpha"] = "beta";
  headers["gamma"] = "delta";
  BufferedSpdyFramer framer(3);
  scoped_ptr<SpdySynReplyControlFrame> control_frame(
      framer.CreateSynReply(1,                        // stream_id
                            CONTROL_FLAG_NONE,
                            true,                     // compress
                            &headers));
  EXPECT_TRUE(control_frame.get() != NULL);

  TestBufferedSpdyVisitor visitor;
  visitor.SimulateInFramer(
      reinterpret_cast<unsigned char*>(control_frame.get()->data()),
       control_frame.get()->length() + SpdyControlFrame::kHeaderSize);
  EXPECT_EQ(0, visitor.error_count_);
  EXPECT_EQ(0, visitor.syn_frame_count_);
  EXPECT_EQ(1, visitor.syn_reply_frame_count_);
  EXPECT_EQ(0, visitor.headers_frame_count_);
  EXPECT_TRUE(CompareHeaderBlocks(&headers, &visitor.headers_));
}

TEST_F(BufferedSpdyFramerSpdy3Test, ReadHeadersHeaderBlock) {
  SpdyHeaderBlock headers;
  headers["alpha"] = "beta";
  headers["gamma"] = "delta";
  BufferedSpdyFramer framer(3);
  scoped_ptr<SpdyHeadersControlFrame> control_frame(
      framer.CreateHeaders(1,                        // stream_id
                           CONTROL_FLAG_NONE,
                           true,                    // compress
                           &headers));
  EXPECT_TRUE(control_frame.get() != NULL);

  TestBufferedSpdyVisitor visitor;
  visitor.SimulateInFramer(
      reinterpret_cast<unsigned char*>(control_frame.get()->data()),
       control_frame.get()->length() + SpdyControlFrame::kHeaderSize);
  EXPECT_EQ(0, visitor.error_count_);
  EXPECT_EQ(0, visitor.syn_frame_count_);
  EXPECT_EQ(0, visitor.syn_reply_frame_count_);
  EXPECT_EQ(1, visitor.headers_frame_count_);
  EXPECT_TRUE(CompareHeaderBlocks(&headers, &visitor.headers_));
}
}  // namespace spdy
