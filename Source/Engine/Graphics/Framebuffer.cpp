#include "Framebuffer.h"

#include <iostream>

#include "../Core.h"

Framebuffer::Framebuffer(Application* app) : Object(app) {
  glGenFramebuffers(1, &framebuffer_);
  glGenRenderbuffers(1, &renderbuffer_);
}

void Framebuffer::Init(unsigned int width, unsigned int height) {
  Bind();

  // texture
  texture_ = std::make_shared<Texture2D>(app_);
  texture_->CreateImage(width, height, nullptr);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_->GetId(), 0);

  // renderbuffer
  glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer_);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer_);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

  Unbind();
}

Texture2D* Framebuffer::GetTexture() { return texture_.get(); }

void Framebuffer::Bind() {
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);
  glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer_);
}

void Framebuffer::Unbind() {
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Framebuffer::~Framebuffer() {
  if (framebuffer_) glDeleteFramebuffers(1, &framebuffer_);
  if (renderbuffer_) glDeleteRenderbuffers(1, &renderbuffer_);
}
