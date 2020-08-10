#include "Framebuffer.h"
#include "VecConsts.h"
#include <memory>
#include <vector>

using namespace VecConsts;

const string Framebuffer::vertexPath_ = "../Shaders/Framebuffer/Framebuffer.vs";

Framebuffer::Framebuffer()
{
    GenMesh();
    glGenFramebuffers(1, &framebuffer_);
}

Framebuffer::Framebuffer(const string& fragmentPath, unsigned int width, unsigned int height)
{
    GenMesh();
    shader_ = GenShader(fragmentPath);
    glGenFramebuffers(1, &framebuffer_);
    GenFramebuffer(width, height);
    GenRenderbuffer(width, height);
}

void Framebuffer::GenMesh()
{
    mesh_ = std::make_shared<Mesh>();
    mesh_->mode_ = GL_TRIANGLE_FAN;

    mesh_->positions_.push_back(LEFT+DOWN);
    mesh_->positions_.push_back(RIGHT+DOWN);
    mesh_->positions_.push_back(RIGHT+UP);
    mesh_->positions_.push_back(LEFT+UP);

    mesh_->texCoords_.push_back(vec2(0, 0));
    mesh_->texCoords_.push_back(vec2(1, 0));
    mesh_->texCoords_.push_back(vec2(1, 1));
    mesh_->texCoords_.push_back(vec2(0, 1));

    mesh_->Generate();
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

void Framebuffer::Draw()
{
    // glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
    // glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    shader_->Use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, colorbuffer_);
    shader_->SetInt("uTexture", 0);
    mesh_->Render();
}

unsigned int Framebuffer::Texture()
{
    Bind();
    shader_->Use();
    mesh_->Render();
    Unbind();
    return colorbuffer_;
}

Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &framebuffer_);
}
