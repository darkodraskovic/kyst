#ifndef ENTITY_H
#define ENTITY_H

#include <string>

#include "../Graphics/Model.h"
#include "Scene.h"

class Entity {
 public:
  Entity();

  virtual void Update(float deltaTime);
  virtual void Draw(const glm::mat4& uView, const glm::mat4& uProjection);

  Scene* GetScene();

  void SetModel(std::shared_ptr<Model> model);
  Model* GetModel();

  std::string name_;
  bool visible_ = true;

  vec3 position_ = vec3(0.f);
  vec3 rotation_ = vec3(0.f);
  vec3 scale_ = vec3(1.f);

  // TODO: make private
  bool remove_ = false;

 protected:
  shared_ptr<Model> model_;

  Scene* scene_;
  friend class Scene;
};

#endif
