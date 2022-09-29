#pragma once

#include <memory>

#include "Texture2D.h"

namespace Kyst {

class Framebuffer {
 public:
  Framebuffer();
  ~Framebuffer();

  void Init(unsigned int width, unsigned int height);
  void Bind();
  Texture2D* GetTexture();

  static void Unbind();

 private:
  std::shared_ptr<Texture2D> texture_;
  unsigned int framebuffer_{0};
  unsigned int renderbuffer_{0};
};

}  // namespace Kyst
