#ifndef CUBE_H
#define CUBE_H

#include <glm/gtc/constants.hpp>

#include "Engine/Scene/Entity.h"
#include "ShapeFactory/CubeFactory.h"

using namespace ShapeFactory;

class Cube : public Entity {
 public:
  Cube(std::shared_ptr<Material> material) : Entity() {
    SetModel(std::make_shared<Model>());
    GetModel()->SetMaterial(material);
    GetModel()->SetMesh(CubeFactory::GetMesh());
    GetModel()->GetMesh()->Generate(material->GetShader()->GetId());
  };

  virtual void Update(float deltaTime) override { rotation_.y += deltaTime * glm::quarter_pi<float>(); };
};

#endif
