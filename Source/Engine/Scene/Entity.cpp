#include "Entity.h"

#include "../VecConsts.h"
#include "Component/ModelComponent.h"
#include "Scene.h"

using namespace VecConsts;

void Entity::SetScene(Scene* scene) { scene_ = scene; }
Scene* Entity::GetScene() { return scene_; }

void Entity::Update(float deltaTime) {
  for (auto it = updatables_.begin(); it != updatables_.end(); ++it) {
    (*it)->Update(deltaTime);
  }
}

void Entity::Draw(const glm::mat4& uView, const glm::mat4& uProjection) {
  glm::mat4 transform = glm::translate(glm::mat4(1.f), position_);
  transform = glm::rotate(transform, rotation_.x, RIGHT);
  transform = glm::rotate(transform, rotation_.y, UP);
  transform = glm::rotate(transform, rotation_.z, FORWARD);
  transform = glm::scale(transform, scale_);

  for (auto it = drawables_.begin(); it != drawables_.end(); ++it) {
    (*it)->Draw(transform, uView, uProjection);
  }

  // model_->Draw(transform, uView, uProjection);
}
