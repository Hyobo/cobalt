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

#include "cobalt/renderer/renderer_module.h"

#include "cobalt/renderer/rasterizer_skia/hardware_rasterizer.h"
#include "cobalt/renderer/rasterizer_skia/software_rasterizer.h"

namespace cobalt {
namespace renderer {

namespace {
scoped_ptr<Rasterizer> CreateRasterizer(
    backend::GraphicsContext* graphics_context) {
#if SB_HAS(GLES2)
  return scoped_ptr<Rasterizer>(
      new rasterizer_skia::SkiaHardwareRasterizer(graphics_context));
#elif SB_HAS(BLITTER)
  // TODO(***REMOVED***): Use hardware rasterizer with hardware blitter.
  return scoped_ptr<Rasterizer>(
      new rasterizer_skia::SkiaSoftwareRasterizer(graphics_context));
#else
#error "Either GLES2 or the Starboard Blitter API must be available."
  return scoped_ptr<Rasterizer>();
#endif
}
}  // namespace

void RendererModule::Options::SetPerPlatformDefaultOptions() {
  create_rasterizer_function = base::Bind(&CreateRasterizer);
}

}  // namespace renderer
}  // namespace cobalt
