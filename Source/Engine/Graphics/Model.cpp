#include "Model.h"

#include "../VecConsts.h"

namespace Kyst {

using namespace VecConsts;
Model::Model() {}

void Model::SetMaterial(std::shared_ptr<Material> material) { material_ = material; }
Material* Model::GetMaterial() { return material_.get(); }

void Model::SetMesh(std::shared_ptr<Mesh> mesh) { mesh_ = mesh; }
Mesh* Model::GetMesh() { return mesh_.get(); }

void Model::Draw(const glm::mat4& uModel, const glm::mat4& uView, const glm::mat4& uProjection) {
  material_->Update(uModel, uView, uProjection);
  mesh_->Draw();
}

}  // namespace Kyst
