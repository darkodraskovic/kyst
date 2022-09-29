#include "Viewport.h"

#include <glm/fwd.hpp>

#include "../Application.h"
#include "../Graphics/Mesh.h"
#include "../Graphics/Texture2D.h"
#include "Component/CameraComponent.h"
#include "Entity.h"
#include "OrthoCamera.h"
#include "PerspectiveCamera.h"
#include "Scene.h"

using namespace std;

namespace Kyst {

const string vertexPath_ = "Shaders/Viewport/Viewport.vs";
const string fragmentPath_ = "Shaders/Viewport/Viewport.fs";

Viewport::Viewport(Application* app) : Object(app){};

void Viewport::Init(unsigned int width, unsigned int height) {
  width_ = width;
  height_ = height;
  GenBuffers(width, height);
  GenQuad(width, height);
  scene_ = make_shared<Scene>();
  scene_->viewport_ = this;
}

void Viewport::GenBuffers(float width, float height) {
  shader_ = make_shared<Shader>(vertexPath_, fragmentPath_);
  frontbuffer_ = make_shared<Framebuffer>();
  frontbuffer_->Init(width_, height_);
  backbuffer_ = make_shared<Framebuffer>();
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
      glBindTexture(GL_TEXTURE_2D, unbound->GetTexture()->GetId());
      effects_[i]->Use();
      effects_[i]->SetInt("uTexture", 0);
      quad_->Draw();
    }
  }

  bound_->Unbind();

  auto size = GetApplication()->GetWindowSize();
  glViewport(0, 0, size.x, size.y);
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
Scene* Viewport::GetScene() { return scene_.get(); }

std::shared_ptr<Viewport> Viewport::Create(Application* app, bool perspective, int width, int height) {
  auto viewport = std::make_shared<Viewport>(app);
  viewport->Init(width, height);

  auto cameraEntity = std::make_shared<Entity>();
  viewport->scene_->AddEntity(cameraEntity);

  std::shared_ptr<Camera> camera;
  if (perspective) {
    camera = make_shared<PerspectiveCamera>();
  } else {
    camera = make_shared<OrthoCamera>();
  }

  auto cameraComponent = cameraEntity->AddComponent<CameraComponent>();
  cameraComponent->SetCamera(camera);
  viewport->scene_->cameraComponent_ = cameraComponent;

  return viewport;
}

}  // namespace Kyst
