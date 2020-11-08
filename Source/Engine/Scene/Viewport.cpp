#include "../Application.h"
#include "../Graphics/Mesh.h"
#include "Source/Engine/Graphics/Framebuffer.h"
#include "Source/Engine/Graphics/Texture2D.h"
#include "Viewport.h"
#include "Scene.h"
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/matrix.hpp>
#include <memory>
#include <vector>

#include "PerspectiveCamera.h"
#include "OrthoCamera.h"

const std::string Viewport::vertexPath_ = "Shaders/Viewport/Viewport.vs";
const std::string Viewport::fragmentPath_ = "Shaders/Viewport/Viewport.fs";

void Viewport::Init(unsigned int width, unsigned int height) {
    width_ = width;
    height_ = height;
    GenBuffers(width, height);
    GenQuad(width, height);
}

void Viewport::GenBuffers(float width, float height) {
    shader_ = std::make_shared<Shader>(vertexPath_, fragmentPath_);
    frontbuffer_ = std::make_shared<Framebuffer>(app_);
    frontbuffer_->Init(width_, height_);
    bound_ = frontbuffer_.get();
    backbuffer_ = std::make_shared<Framebuffer>(app_);
    backbuffer_->Init(width_, height_);
}

void Viewport::GenQuad(float width, float height) {
    quad_ = std::make_shared<Mesh>();
    quad_->mode_ = GL_TRIANGLE_FAN;

    scale_.x = width / app_->GetWindowSize().x;
    scale_.y = height / app_->GetWindowSize().y;

    quad_->positions_.push_back(vec3(-1, -1, 0));
    quad_->positions_.push_back(vec3(1, -1, 0));
    quad_->positions_.push_back(vec3(1, 1, 0));
    quad_->positions_.push_back(vec3(-1, 1, 0));

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
    glViewport(0, 0, width_, height_);
    
    frontbuffer_->Bind();
    scene_->Draw(width_, height_);
    bound_ = frontbuffer_.get();

    if (!effects_.empty()) {
        glDisable(GL_DEPTH_TEST);
        glActiveTexture(GL_TEXTURE0);
        Framebuffer* unbound = backbuffer_.get();
        for (int i = 0; i < effects_.size(); i++) {
            bound_->Unbind();
            unbound->Bind();
            Framebuffer* tmp = bound_;
            bound_ = unbound;
            unbound = tmp;
            glBindTexture(GL_TEXTURE_2D, unbound->texture_->GetId());
            effects_[i]->Use();
            effects_[i]->SetInt("uTexture", 0);
            quad_->Render();
        }
    }

    bound_->Unbind();
    
    glViewport(0, 0, app_->GetWindowSize().x, app_->GetWindowSize().y);
}

void Viewport::Draw() {
    glDisable(GL_DEPTH_TEST);

    shader_->Use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, bound_->GetTexture()->GetId());
    shader_->SetInt("uTexture", 0);
    auto transform = glm::mat4(1.f);
    transform = glm::translate(transform, position_);
    transform = glm::scale(transform, scale_);
    shader_->SetMat4("uModel", transform);

    quad_->Render();
}

void Viewport::Update(float deltaTime) {
    scene_->Update(deltaTime);
    Render();
    Draw();
}

Texture2D* Viewport::GetTexture() {
    return bound_->GetTexture();
}

Viewport* Viewport::Create(Application* app, bool perspective, int width, int height) {
    auto viewport = new Viewport(app);
    viewport->Init(width, height);
    
    std::shared_ptr<Camera> cam;
    if (perspective) cam = std::make_shared<PerspectiveCamera>(app);
    else  cam = std::make_shared<OrthoCamera>(app);
    
    auto scene = std::make_shared<Scene>(app);
    scene->camera_ = cam;

    viewport->scene_ = scene;
    
    return viewport;
}
