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

#ifndef COBALT_RENDERER_BACKEND_EGL_GRAPHICS_CONTEXT_H_
#define COBALT_RENDERER_BACKEND_EGL_GRAPHICS_CONTEXT_H_

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "base/memory/ref_counted.h"
#include "base/optional.h"
#include "cobalt/base/polymorphic_downcast.h"
#include "cobalt/renderer/backend/egl/render_target.h"
#include "cobalt/renderer/backend/egl/resource_context.h"
#include "cobalt/renderer/backend/graphics_context.h"
#include "cobalt/renderer/backend/texture.h"

namespace cobalt {
namespace renderer {
namespace backend {

// Encapsulates a context created via EGL, which implies that it makes
// accessible the OpenGL ES API.
class GraphicsContextEGL : public GraphicsContext {
 public:
  GraphicsContextEGL(GraphicsSystem* parent_system, EGLDisplay display,
                     EGLConfig config, ResourceContext* resource_context);
  ~GraphicsContextEGL() OVERRIDE;

  scoped_ptr<Texture> CreateTexture(
      scoped_ptr<TextureData> texture_data) OVERRIDE;

  scoped_ptr<Texture> CreateTextureFromRawMemory(
      const scoped_refptr<ConstRawTextureMemory>& raw_texture_memory,
      intptr_t offset, const SurfaceInfo& surface_info,
      int pitch_in_bytes) OVERRIDE;

  scoped_refptr<RenderTarget> CreateOffscreenRenderTarget(
      const math::Size& dimensions) OVERRIDE;
  scoped_ptr<Texture> CreateTextureFromOffscreenRenderTarget(
      const scoped_refptr<RenderTarget>& render_target) OVERRIDE;
  scoped_array<uint8_t> GetCopyOfTexturePixelDataAsRGBA(
      const Texture& texture) OVERRIDE;

  scoped_ptr<GraphicsContext::Frame> StartFrame(
      const scoped_refptr<backend::RenderTarget>& render_target) OVERRIDE;

  // Helper class to allow one to create a RAII object that will acquire the
  // current context upon construction and release it upon destruction.
  class ScopedMakeCurrent {
   public:
    explicit ScopedMakeCurrent(GraphicsContextEGL* graphics_context)
        : graphics_context_(graphics_context),
          was_current_(graphics_context_->is_current_),
          previous_current_surface_(graphics_context_->current_surface_) {
      graphics_context_->MakeCurrent();
    }
    ScopedMakeCurrent(GraphicsContextEGL* graphics_context, EGLSurface surface)
        : graphics_context_(graphics_context),
          was_current_(graphics_context_->is_current_),
          previous_current_surface_(graphics_context_->current_surface_) {
      graphics_context_->MakeCurrentWithSurface(surface);
    }
    ~ScopedMakeCurrent() {
      if (was_current_) {
        graphics_context_->MakeCurrentWithSurface(previous_current_surface_);
      } else {
        graphics_context_->ReleaseCurrentContext();
      }
    }

   private:
    GraphicsContextEGL* graphics_context_;
    bool was_current_;
    EGLSurface previous_current_surface_;
  };

  // Helper methods to make this context current and associate it with
  // a surface.  In EGL, a context is either not current or it is current and
  // associated with a surface.  For all functionality (e.g. texture creation)
  // that is provided but does not require a surface binding, null_surface_ is
  // specified as a surface.
  void MakeCurrentWithSurface(EGLSurface surface);

  // Alternatively, this call can be made to make the context current along
  // with a null surface.  You would be interested in this method if you don't
  // plan to be making any draw calls, such as if you're setting up a texture.
  void MakeCurrent() OVERRIDE;
  void ReleaseCurrentContext() OVERRIDE;

 private:
  // Performs a test to determine if the pixel data returned by glReadPixels
  // needs to be vertically flipped or not.  This test is expensive and so
  // it should be only done once and the results cached.
  bool ComputeReadPixelsNeedVerticalFlip();

  // Sets up all structures (like Shaders and vertex buffers) required to
  // support the Frame::BlitToRenderTarget() functionality.
  void SetupBlitToRenderTargetObjects();

  class Frame : public GraphicsContext::Frame {
   public:
    Frame(GraphicsContextEGL* owner, EGLSurface surface);
    ~Frame();

    void Clear(float red, float green, float blue, float alpha) OVERRIDE;
    void BlitToRenderTarget(const Texture& texture) OVERRIDE;

   private:
    GraphicsContextEGL* owner_;
    ScopedMakeCurrent scoped_make_current_;
  };
  friend class Frame;
  void OnFrameEnd();

  EGLDisplay display_;

  // The EGL/OpenGL ES context hosted by this GraphicsContextEGL object.
  EGLContext context_;
  EGLConfig config_;

  // Keep track of whether this context has been set to current or not, and
  // if so what surface was associated with it.
  bool is_current_;
  EGLSurface current_surface_;

  // A dummy surface that is made current when we wish to execute OpenGL ES
  // commands that don't actually involve a surface in any way (e.g. texture
  // creation).
  EGLSurface null_surface_;

  // Cache whether or not BGRA texture format is supported by the underlying
  // OpenGL ES implementation.
  bool bgra_format_supported_;

  // Active whenever a frame is started and a render target is bound to us.
  scoped_refptr<RenderTargetEGL> render_target_;

  // Data required to provide BlitToRenderTarget() functionality via OpenGL ES.
  GLuint blit_vertex_shader_;
  GLuint blit_fragment_shader_;
  static const int kBlitPositionAttribute = 0;
  static const int kBlitTexcoordAttribute = 1;
  GLuint blit_program_;
  GLuint blit_vertex_buffer_;

  // Lazily evaluate whether we need to do a vertical flip when calling
  // glReadPixels(), and cache the result here when that question is answered.
  base::optional<bool> read_pixels_needs_vertical_flip_;

  // When creating and destroying textures, OpenGL calls need to be made with
  // a GL context current.  By making TextureEGL a friend class of
  // GraphicsContextEGL, the tight relationship and association of a TextureEGL
  // with a GraphicsContextEGL is made more explicit, and it also allows
  // TextureEGL to access MakeCurrent()/ReleaseCurrentContext() methods
  // of GraphicsContextEGL.
  friend class TextureEGL;
};

}  // namespace backend
}  // namespace renderer
}  // namespace cobalt

#endif  // COBALT_RENDERER_BACKEND_EGL_GRAPHICS_CONTEXT_H_
