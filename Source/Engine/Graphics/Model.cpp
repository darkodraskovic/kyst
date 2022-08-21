#include "Model.h"

#include "../VecConsts.h"

using namespace VecConsts;

Model::Model() {}

Model::Model(Mesh* mesh, Material* material) {
  mesh_ = std::shared_ptr<Mesh>(mesh);
  material_ = std::shared_ptr<Material>(material);
}

void Model::Draw(const glm::mat4& uModel, const glm::mat4& uView, const glm::mat4& uProjection) {
  material_->Update(uModel, uView, uProjection);
  mesh_->Draw();
}
