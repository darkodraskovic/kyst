#include "ModelComponent.h"

namespace Kyst {

void ModelComponent::SetModel(std::shared_ptr<Model> model) { model_ = model; }
Model* ModelComponent::GetModel() { return model_.get(); }

void ModelComponent::Draw(const glm::mat4& uModel, const glm::mat4& uView, const glm::mat4& uProjection) {
  model_->Draw(uModel, uView, uProjection);
}

}  // namespace Kyst
