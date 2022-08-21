#ifndef ENTITY_H
#define ENTITY_H

#include <string>

#include "../Graphics/Model.h"
#include "Scene.h"

class Entity {
 public:
  Entity();
  Entity(Mesh* mesh, Material* material);

  virtual void Update(float deltaTime);
  virtual void Draw(const glm::mat4& uView, const glm::mat4& uProjection);
  Scene* GetScene();
  Model* GetModel();

  std::string name_;
  bool visible_ = true;

  vec3 position_ = vec3(0.f);
  vec3 rotation_ = vec3(0.f);
  vec3 scale_ = vec3(1.f);

  bool remove_ = false;

 private:
  shared_ptr<Model> model_;

  Scene* scene_;
  friend class Scene;
};

#endif
