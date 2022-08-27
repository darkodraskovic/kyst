#include "Viewport.h"

#include <glm/fwd.hpp>

#include "../Application.h"
#include "../Graphics/Mesh.h"
#include "../Graphics/Texture2D.h"
#include "OrthoCamera.h"
#include "PerspectiveCamera.h"
#include "Scene.h"

using namespace std;

const string vertexPath_ = "Shaders/Viewport/Viewport.vs";
const string fragmentPath_ = "Shaders/Viewport/Viewport.fs";

void Viewport::Init(unsigned int width, unsigned int height) {
  width_ = width;
  height_ = height;
  GenBuffers(width, height);
  GenQuad(width, height);
}

void Viewport::GenBuffers(float width, float height) {
  shader_ = make_shared<Shader>(vertexPath_, fragmentPath_);
  frontbuffer_ = make_shared<Framebuffer>(app_);
  frontbuffer_->Init(width_, height_);
  backbuffer_ = make_shared<Framebuffer>(app_);
  backbuffer_->Init(width_, height_);
}

void Viewport::GenQuad(float width, float height) {
  quad_ = make_shared<Mesh>();
  quad_->mode_ = GL_TRIANGLE_FAN;

  quad_->positions_.push_back(vec3(-1, -1, 0));
  quad_->positions_.push_back(vec3(1, -1, 0));
  quad_->positions_.push_back(vec3(1, 1, 0));
  quad_->positions_.push_back(vec3(-1, 1, 0));

  quad_->texCoords_.push_back(vec2(0, 0));
  quad_->texCoords_.push_back(vec2(1, 0));
  quad_->texCoords_.push_back(vec2(1, 1));
  quad_->texCoords_.push_back(vec2(0, 1));

  quad_->Generate(shader_->GetId());
}

void Viewport::AddEffect(const char* fragmentPath) {
  auto effect = make_shared<Shader>(vertexPath_, fragmentPath);
  effects_.push_back(effect);
}

void Viewport::DrawToBuffer() {
  glViewport(0, 0, width_, height_);
  frontbuffer_->Bind();
  bound_ = frontbuffer_.get();

  // render scene
  scene_->Draw(width_, height_);

  // render effects
  if (!effects_.empty()) {
    glDisable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE0);
    Framebuffer* unbound = backbuffer_.get();
    for (int i = 0; i < effects_.size(); i++) {
      // switch buffers
      bound_->Unbind();
      unbound->Bind();
      Framebuffer* tmp = bound_;
      bound_ = unbound;
      unbound = tmp;

      // render unbound buffer's texture to bound buffer
      glBindTexture(GL_TEXTURE_2D, unbound->texture_->GetId());
      effects_[i]->Use();
      effects_[i]->SetInt("uTexture", 0);
      quad_->Draw();
    }
  }

  bound_->Unbind();
  glViewport(0, 0, app_->GetWindowSize().x, app_->GetWindowSize().y);
}

void Viewport::DrawToScreen() {
  glDisable(GL_DEPTH_TEST);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, bound_->GetTexture()->GetId());

  shader_->Use();
  shader_->SetInt("uTexture", 0);
  glm::mat4 transform = glm::translate(glm::mat4(1.f), position_);
  transform = glm::scale(transform, scale_);
  shader_->SetMat4("uModel", transform);

  quad_->Draw();
}

void Viewport::Update(float deltaTime) { scene_->Update(deltaTime); }

void Viewport::Render() {
  DrawToBuffer();
  DrawToScreen();
}

Texture2D* Viewport::GetTexture() { return bound_->GetTexture(); }

Viewport* Viewport::Create(Application* app, bool perspective, int width, int height) {
  Viewport* viewport = new Viewport(app);
  viewport->Init(width, height);
  viewport->scene_ = make_shared<Scene>(app);
  if (perspective)
    viewport->scene_->camera_ = make_shared<PerspectiveCamera>(app);
  else
    viewport->scene_->camera_ = make_shared<OrthoCamera>(app);
  return viewport;
}
