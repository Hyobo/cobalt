/*
 * Copyright 2015 Google Inc. All Rights Reserved.
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

#include "media/base/shell_video_frame_provider.h"

#include "base/logging.h"
#include "media/base/pipeline.h"

namespace media {

ShellVideoFrameProvider::ShellVideoFrameProvider() {
#if !defined(__LB_SHELL__FOR_RELEASE__)
  dropped_frames_ = 0;
  max_delay_in_microseconds_ = 0;
#endif  // !defined(__LB_SHELL__FOR_RELEASE__)
}

const scoped_refptr<VideoFrame>& ShellVideoFrameProvider::GetCurrentFrame() {
  const int kEpsilonInMicroseconds =
      base::Time::kMicrosecondsPerSecond / 60 / 2;

  base::AutoLock auto_lock(frames_lock_);

  base::TimeDelta media_time = Pipeline::GetCurrentTime();
  while (!frames_.empty()) {
    int64_t frame_time = frames_[0]->GetTimestamp().InMicroseconds();
    if (frame_time >= media_time.InMicroseconds())
      break;
    if (current_frame_ != frames_[0] &&
        frame_time + kEpsilonInMicroseconds >= media_time.InMicroseconds())
      break;

#if !defined(__LB_SHELL__FOR_RELEASE__)
    const bool kLogFrameDrops ALLOW_UNUSED = false;
    if (current_frame_ != frames_[0]) {
      ++dropped_frames_;
      if (media_time.InMicroseconds() - frame_time > max_delay_in_microseconds_)
        max_delay_in_microseconds_ = media_time.InMicroseconds() - frame_time;
      DLOG_IF(WARNING, kLogFrameDrops)
          << "dropped one frame with timestamp "
          << frames_[0]->GetTimestamp().InMicroseconds()
          << " at media time " << media_time.InMicroseconds()
          << " total dropped " << dropped_frames_
          << " frames with a max delay of " << max_delay_in_microseconds_
          << " ms";
    }
#endif  // !defined(__LB_SHELL__FOR_RELEASE__)

    frames_.erase(frames_.begin());
  }
  if (!frames_.empty()) {
    current_frame_ = frames_[0];
  }
  return current_frame_;
}

void ShellVideoFrameProvider::AddFrame(const scoped_refptr<VideoFrame>& frame) {
  base::AutoLock auto_lock(frames_lock_);
  frames_.push_back(frame);
}

void ShellVideoFrameProvider::Flush() {
  base::AutoLock auto_lock(frames_lock_);
  frames_.clear();
}

void ShellVideoFrameProvider::Stop() {
  base::AutoLock auto_lock(frames_lock_);
  frames_.clear();
  current_frame_ = NULL;
}

size_t ShellVideoFrameProvider::GetNumOfFramesCached() const {
  base::AutoLock auto_lock(frames_lock_);
  return frames_.size();
}

}  // namespace media
