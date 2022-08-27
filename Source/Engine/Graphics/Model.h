#pragma once

#include <string>

#include "Material.h"
#include "Mesh.h"

class Model {
 public:
  Model();

  virtual void Draw(const glm::mat4& uModel, const glm::mat4& uView, const glm::mat4& uProjection);

  void SetMaterial(std::shared_ptr<Material> material);
  Material* GetMaterial();

  void SetMesh(std::shared_ptr<Mesh> mesh);
  Mesh* GetMesh();

 private:
  std::shared_ptr<Material> material_;
  std::shared_ptr<Mesh> mesh_;
};
