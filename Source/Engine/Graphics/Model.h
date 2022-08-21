#pragma once

#include <string>

#include "Material.h"
#include "Mesh.h"

class Model {
 public:
  Model();
  Model(Mesh* mesh, Material* material);

  virtual void Draw(const glm::mat4& uModel, const glm::mat4& uView, const glm::mat4& uProjection);

  std::shared_ptr<Material> material_;
  std::shared_ptr<Mesh> mesh_;
};
