#include <iostream>

#include "../Core.h"
#include "Framebuffer.h"


Framebuffer::Framebuffer(Application* app) : Object(app) {
    glGenFramebuffers(1, &framebuffer_);
}

void Framebuffer::Init(unsigned int width, unsigned int height) {
    Bind();

    texture_ = new Texture2D(app_);
    texture_->CreateImage(width, height, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_->GetTexture(), 0);

    glGenRenderbuffers(1, &renderbuffer_);
    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer_);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer_);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

    Unbind();
}

void Framebuffer::Bind() { glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_); }
void Framebuffer::Unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &framebuffer_);
}
