// Copyright 2015 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "starboard/nplb/time_constants.h"
#include "starboard/time.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace {

TEST(SbTimeGetMonotonicNowTest, IsMonotonic) {
  const int kNumIterations = 100;
  for (int i = 0; i < kNumIterations; ++i) {
    SbTimeMonotonic time1 = SbTimeGetMonotonicNow();
    SbTime clockStart = SbTimeGetNow();

    // Spin tightly until time increments.
    SbTimeMonotonic time2 = 0;
    while (true) {
      time2 = SbTimeGetMonotonicNow();
      if (time2 != time1) {
        EXPECT_GT(time2, time1);
        EXPECT_LT(time2 - time1, kSbTimeSecond);
        return;
      }

      // If time hasn't increased within a second, our high-resolution monotimic
      // timer is broked.
      if (SbTimeGetNow() - clockStart >= kSbTimeSecond) {
        GTEST_FAIL() << "SbTimeGetMonotonicNow() hasn't changed within a second.";
        return;
      }
    }
  }
}

}  // namespace
