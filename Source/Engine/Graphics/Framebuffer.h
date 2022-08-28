#ifndef FRAMBUFFER_H
#define FRAMBUFFER_H

#include <memory>

#include "../Object.h"
#include "Texture2D.h"

class Framebuffer : public Object {
 public:
  Framebuffer(Application* app);
  ~Framebuffer();

  void Init(unsigned int width, unsigned int height);
  void Bind();
  Texture2D* GetTexture();

  static void Unbind();

 private:
  std::shared_ptr<Texture2D> texture_;
  unsigned int framebuffer_;
  unsigned int renderbuffer_;

  friend class Viewport;
};

#endif /* FRAMBUFFER_H */
