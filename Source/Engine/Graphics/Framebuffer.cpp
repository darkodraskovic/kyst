#include <glad/glad.h>
#include <glm/fwd.hpp>
#include <iostream>
#include "Framebuffer.h"

Framebuffer::Framebuffer()
{
    mesh_ = std::make_shared<Mesh>();
    mesh_->mode_ = GL_TRIANGLES;

    // aPos
    vec2 aPos = vec2(-1, -1);
    vec2 bPos = vec2(1, -1);
    vec2 cPos = vec2(1, 1);
    vec2 dPos = vec2(-1, 1);
    std::vector<vec2> pos;
    pos.push_back(aPos);
    pos.push_back(bPos);
    pos.push_back(dPos);
    pos.push_back(bPos);
    pos.push_back(cPos);
    pos.push_back(dPos);
    mesh_->GenArrayBuffer(pos);

    // aTexCoords
    vec2 aTexCoord = vec2(0, 0);
    vec2 bTexCoord = vec2(1, 0);
    vec2 cTexCoord = vec2(1, 1);
    vec2 dTexCoord = vec2(0, 1);
    std::vector<vec2> texCoords;
    texCoords.push_back(aTexCoord);
    texCoords.push_back(bTexCoord);
    texCoords.push_back(dTexCoord);
    texCoords.push_back(bTexCoord);
    texCoords.push_back(cTexCoord);
    texCoords.push_back(dTexCoord);
    mesh_->GenArrayBuffer(texCoords);
}

void Framebuffer::GenFramebuffer(unsigned int width, unsigned int height)
{
    
    glGenFramebuffers(1, &framebuffer_);
    
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

unsigned int Framebuffer::GenTexture(unsigned int width, unsigned int height, const char* fragmentPath)
{
    auto shader = std::make_shared<Shader>("../Shaders/Tex2D.vs", fragmentPath);
    GenFramebuffer(width, height);

    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    shader->Use();
    mesh_->Render();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    return colorbuffer_;
}