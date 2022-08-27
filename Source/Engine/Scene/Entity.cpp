#include "Entity.h"

#include "../VecConsts.h"

using namespace VecConsts;

Entity::Entity() {}

Scene* Entity::GetScene() { return scene_; }

void Entity::SetModel(std::shared_ptr<Model> model) { model_ = model; }
Model* Entity::GetModel() { return model_.get(); }

void Entity::Update(float deltaTime) {}

void Entity::Draw(const glm::mat4& uView, const glm::mat4& uProjection) {
  glm::mat4 transform = glm::translate(glm::mat4(1.f), position_);
  transform = glm::rotate(transform, rotation_.x, RIGHT);
  transform = glm::rotate(transform, rotation_.y, UP);
  transform = glm::rotate(transform, rotation_.z, FORWARD);
  transform = glm::scale(transform, scale_);
  model_->Draw(transform, uView, uProjection);
}
