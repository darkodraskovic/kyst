#include "Framebuffer.h"
#include "VecConsts.h"
#include "Viewport.h"
#include <vector>

using namespace VecConsts;

const string Framebuffer::vertexPath_ = "../Shaders/Framebuffer/Framebuffer.vs";

Framebuffer::Framebuffer(unsigned int width, unsigned int height)
{
    glGenFramebuffers(1, &framebuffer_);
    GenFramebuffer(width, height);
    GenRenderbuffer(width, height);    
}

Framebuffer::Framebuffer(const string& fragmentPath, unsigned int width, unsigned int height)
{
    glGenFramebuffers(1, &framebuffer_);
    GenFramebuffer(width, height);
    GenRenderbuffer(width, height);

    quad_ = Viewport::GenQuad();
    shader_ = GenShader(fragmentPath);    
}

void Framebuffer::GenFramebuffer(unsigned int width, unsigned int height)
{
    
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);
    glGenTextures(1, &colorbuffer_);
    glBindTexture(GL_TEXTURE_2D, colorbuffer_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorbuffer_, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);    
}

void Framebuffer::GenRenderbuffer(unsigned int width, unsigned int height)
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);
    glGenRenderbuffers(1, &renderbuffer_);
    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer_);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer_);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);    
}

std::shared_ptr<Shader> Framebuffer::GenShader(const std::string& fragmentPath)
{
    return std::make_shared<Shader>(vertexPath_, fragmentPath);
}

void Framebuffer::Bind() { glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_); }
void Framebuffer::Unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

unsigned int Framebuffer::Texture()
{
    Bind();
    shader_->Use();
    quad_->Render();
    Unbind();
    return colorbuffer_;
}

Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &framebuffer_);
}
