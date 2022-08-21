#ifndef CUBE_H
#define CUBE_H

#include <glm/gtc/constants.hpp>

#include "Engine/Scene/Entity.h"
#include "ShapeFactory/CubeFactory.h"

using namespace ShapeFactory;

class Cube : public Entity {
 public:
  Cube(const std::shared_ptr<Material>& material) : Entity() {
    Model* model = GetModel();
    GetModel()->material_ = material;
    GetModel()->mesh_ = CubeFactory::GetMesh();
    GetModel()->mesh_->Generate(material->shader_->id_);
  };

  virtual void Update(float deltaTime) override { rotation_.y += deltaTime * glm::quarter_pi<float>(); };
};

#endif
