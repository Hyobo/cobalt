/*
 * Copyright 2016 Google Inc. All Rights Reserved.
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

#ifndef GLIMP_GLES_PIXEL_FORMAT_H_
#define GLIMP_GLES_PIXEL_FORMAT_H_

#include <GLES3/gl3.h>

#include "glimp/gles/buffer_impl.h"
#include "glimp/nb/ref_counted.h"
#include "glimp/nb/scoped_ptr.h"

namespace glimp {
namespace gles {

// An internal structure which maintains information on a limited number of
// glimp-supported pixel formats for both textures and render targets.
enum PixelFormat {
  kPixelFormatRGBA8,
  kPixelFormatARGB8,
  kPixelFormatBGRA8,
  kPixelFormatRGB565,
  kPixelFormatA8,
  kPixelFormatInvalid,
};

// Returns the number of bytes per pixel for a given PixelFormat.
int BytesPerPixel(PixelFormat format);

// Converts a GL type and format to a glimp PixelFormat.  Information about
// the different possible values for type and format can be found here:
//   https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexImage2D.xml
// Note that glimp may not support all possible formats described above.
PixelFormat PixelFormatFromGLTypeAndFormat(GLenum format, GLenum type);

}  // namespace gles
}  // namespace glimp

#endif  // GLIMP_GLES_PIXEL_FORMAT_H_
