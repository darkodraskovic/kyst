#include "Viewport.h"
#include "VecConsts.h"

using namespace VecConsts;

const std::string Viewport::vertexPath_ = "../Shaders/Viewport/Viewport.vs";
const std::string Viewport::fragmentPath_ = "../Shaders/Viewport/Viewport.fs";

Viewport::Viewport(unsigned int width, unsigned int height)
{
    quad_ = GenQuad();
    shader_ = std::make_shared<Shader>(vertexPath_, fragmentPath_);
    frontbuffer_ = std::make_shared<Framebuffer>(width, height);
    backbuffer_ = std::make_shared<Framebuffer>(width, height);
}

std::shared_ptr<Mesh> Viewport::GenQuad()
{
    auto quad = std::make_shared<Mesh>();
    quad->mode_ = GL_TRIANGLE_FAN;

    quad->positions_.push_back(LEFT+DOWN);
    quad->positions_.push_back(RIGHT+DOWN);
    quad->positions_.push_back(RIGHT+UP);
    quad->positions_.push_back(LEFT+UP);

    quad->texCoords_.push_back(vec2(0, 0));
    quad->texCoords_.push_back(vec2(1, 0));
    quad->texCoords_.push_back(vec2(1, 1));
    quad->texCoords_.push_back(vec2(0, 1));

    quad->Generate();
    return quad;
}

void Viewport::AddEffect(const char *fragmentPath)
{
    auto effect = std::make_shared<Shader>(Viewport::vertexPath_, fragmentPath);
    effects_.push_back(effect);
}

void Viewport::Bind()
{
    frontbuffer_->Bind();    
}

void Viewport::Render()
{
    auto bound = frontbuffer_;
    if (!effects_.empty()) {
        auto unbound = backbuffer_;
        for (int i = 0; i < effects_.size(); i++) {
            bound->Unbind();
            unbound->Bind();
            auto tmp = bound;
            bound = unbound;
            unbound = tmp;
            Draw(effects_[i].get(), unbound->colorbuffer_);
        }
    }
    bound->Unbind();
    Draw(shader_.get(), bound->colorbuffer_);
}

void Viewport::Draw(Shader* shader, unsigned int texture)
{
    glDisable(GL_DEPTH_TEST);
    shader->Use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    shader->SetInt("uTexture", 0);
    quad_->Render();
}
