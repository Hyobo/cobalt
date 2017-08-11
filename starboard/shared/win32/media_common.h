// Copyright 2017 Google Inc. All Rights Reserved.
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

#ifndef STARBOARD_SHARED_WIN32_MEDIA_COMMON_H_
#define STARBOARD_SHARED_WIN32_MEDIA_COMMON_H_

#include <Mfapi.h>
#include <Mferror.h>
#include <Mfidl.h>
#include <Mfobjects.h>
#include <Rpc.h>
#include <comutil.h>
#include <wrl\client.h>  // For ComPtr.
#include <vector>

#include "starboard/common/ref_counted.h"
#include "starboard/configuration.h"
#include "starboard/log.h"
#include "starboard/media.h"
#include "starboard/mutex.h"
#include "starboard/shared/starboard/player/closure.h"
#include "starboard/shared/starboard/player/filter/player_components.h"
#include "starboard/shared/starboard/player/input_buffer_internal.h"
#include "starboard/shared/starboard/player/video_frame_internal.h"
#include "starboard/string.h"

namespace starboard {
namespace shared {
namespace win32 {

using Closure = ::starboard::shared::starboard::player::Closure;
using DecodedAudio = ::starboard::shared::starboard::player::DecodedAudio;
using DecodedAudioPtr = ::starboard::scoped_refptr<DecodedAudio>;
using InputBuffer = ::starboard::shared::starboard::player::InputBuffer;
using PlayerComponents =
    ::starboard::shared::starboard::player::filter::PlayerComponents;
using Status =
    ::starboard::shared::starboard::player::filter::HostedVideoDecoder::Status;
using VideoFrame = ::starboard::shared::starboard::player::VideoFrame;
using VideoFramePtr = ::starboard::scoped_refptr<VideoFrame>;
using VideoParameters =
    ::starboard::shared::starboard::player::filter::VideoParameters;
using Microsoft::WRL::ComPtr;

// Converts 90khz to 10Mhz (100ns time).
int64_t ConvertToWin32Time(SbMediaTime input);

// Convert the other way around.
SbMediaTime ConvertToMediaTime(int64_t input);

std::vector<ComPtr<IMFMediaType>> GetAllOutputMediaTypes(IMFTransform* decoder);

std::vector<ComPtr<IMFMediaType>> FilterMediaBySubType(
    const std::vector<ComPtr<IMFMediaType>>& input,
    GUID sub_type_filter);

ComPtr<IMFMediaType> FindMediaType(GUID sub_type, IMFTransform* decoder);

}  // namespace win32
}  // namespace shared
}  // namespace starboard

#endif  // STARBOARD_SHARED_WIN32_MEDIA_COMMON_H_
