#include "Scene.h"

#include <algorithm>
#include <iostream>

#include "Entity.h"

void Scene::AddEntity(std::shared_ptr<Entity> entity) {
  if (std::find(entities_.begin(), entities_.end(), entity) != entities_.end()) return;

  entitiesToCreate_.push_back(entity);
}

void Scene::Update(float deltaTime) {
  // remove entities
  for (auto it = entities_.begin(); it != entities_.end(); ++it) {
    if ((*it)->remove_) entities_.erase(it--);
  }

  // update entities
  for (std::shared_ptr<Entity>& e : entities_) {
    e->Update(deltaTime);
  }

  // create entities
  for (std::shared_ptr<Entity>& e : entitiesToCreate_) {
    entities_.push_back(e);
    e->scene_ = this;
  }
  entitiesToCreate_.clear();
};

void Scene::Draw(unsigned int width, unsigned int height) {
  glClearColor(clearColor_.r, clearColor_.g, clearColor_.b, clearColor_.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  glm::mat4 view = camera_->GetViewMatrix();
  glm::mat4 projection = camera_->GetProjectionMatrix(width, height);

  // render solid entities
  glEnable(GL_CULL_FACE);
  for (auto it = entities_.begin(); it != entities_.end(); ++it) {
    auto e = *it;
    if (!e->visible_) continue;
    if (e->GetModel()->GetMaterial()->alpha_ < 1.0) {
      alphaEntities_.push_back(e);
      continue;
    }
    e->Draw(view, projection);
  }
  glDisable(GL_CULL_FACE);

  // render transparent entities
  std::sort(alphaEntities_.begin(), alphaEntities_.end(), [this](std::shared_ptr<Entity> lhs, std::shared_ptr<Entity> rhs) {
    return glm::length(lhs->position_ - camera_->position_) < glm::length(rhs->position_ - camera_->position_);
  });
  glEnable(GL_BLEND);
  for (auto it = alphaEntities_.begin(); it != alphaEntities_.end(); ++it) {
    (*it)->Draw(view, projection);
  }
  glDisable(GL_BLEND);

  alphaEntities_.clear();
}
