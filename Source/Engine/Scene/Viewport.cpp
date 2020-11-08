#include "../Application.h"
#include "../Graphics/Mesh.h"
#include "Viewport.h"
#include "Scene.h"
#include <vector>

const std::string Viewport::vertexPath_ = "Shaders/Viewport/Viewport.vs";
const std::string Viewport::fragmentPath_ = "Shaders/Viewport/Viewport.fs";

void Viewport::Init(const uvec2& size) {
    scene_ = std::make_shared<Scene>(std::make_shared<Camera>(app_));
    Init(size.x, size.y);
}

void Viewport::Init(const uvec2& size, std::shared_ptr<Scene> scene) {
    scene_ = scene;
    Init(size.x, size.y);
}

void Viewport::Init(unsigned int width, unsigned int height) {
    width_ = width;
    height_ = height;
    scene_->viewport_ = this;
    GenBuffers(width, height);
    GenQuad(width, height);
}

Application* Viewport::GetApplication() { return application_;}

Scene* Viewport::GetScene() { return scene_.get(); }

void Viewport::GenBuffers(float width, float height) {
    shader_ = std::make_shared<Shader>(vertexPath_, fragmentPath_);
    frontbuffer_ = std::make_shared<Framebuffer>(app_);
    frontbuffer_->Init(width_, height_);
    backbuffer_ = std::make_shared<Framebuffer>(app_);
    backbuffer_->Init(width_, height_);
}

void Viewport::GenQuad(float width, float height) {
    quad_ = std::make_shared<Mesh>();
    quad_->mode_ = GL_TRIANGLE_FAN;

    float right = -1 + 2 * (width / app_->GetWindowSize().x);
    float up = -1 + 2 * (height / app_->GetWindowSize().y);

    quad_->positions_.push_back(vec3(-1, -1, 0));
    quad_->positions_.push_back(vec3(right, -1, 0));
    quad_->positions_.push_back(vec3(right, up, 0));
    quad_->positions_.push_back(vec3(-1, up, 0));

    quad_->texCoords_.push_back(vec2(0, 0));
    quad_->texCoords_.push_back(vec2(1, 0));
    quad_->texCoords_.push_back(vec2(1, 1));
    quad_->texCoords_.push_back(vec2(0, 1));

    quad_->Generate(shader_->id_);
}

void Viewport::AddEffect(const char *fragmentPath) {
    auto effect = std::make_shared<Shader>(Viewport::vertexPath_, fragmentPath);
    effects_.push_back(effect);
}


void Viewport::Render() {
    frontbuffer_->Bind();
    scene_->Draw(width_, height_);
    auto bound = frontbuffer_;

    if (!effects_.empty()) {
        glDisable(GL_DEPTH_TEST);
        glActiveTexture(GL_TEXTURE0);
        auto unbound = backbuffer_;
        for (int i = 0; i < effects_.size(); i++) {
            bound->Unbind();
            unbound->Bind();
            auto tmp = bound;
            bound = unbound;
            unbound = tmp;
            glBindTexture(GL_TEXTURE_2D, unbound->texture_->GetTexture());
            effects_[i]->Use();
            effects_[i]->SetInt("uTexture", 0);
            quad_->Render();
        }
    }

    bound->Unbind();
    texture_ = bound->texture_->GetTexture();
}

void Viewport::Draw() {
    glDisable(GL_DEPTH_TEST);

    shader_->Use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_);
    shader_->SetInt("uTexture", 0);
    shader_->SetMat4("uModel", glm::translate(glm::mat4(1.f), position_));

    quad_->Render();
}

void Viewport::Update(float deltaTime) {
    scene_->Update(deltaTime);
    Render();
    Draw();
}

unsigned int Viewport::GetTexture() {
    return texture_;
}
