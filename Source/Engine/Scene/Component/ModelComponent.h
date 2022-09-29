#pragma once

#include <memory>

#include "../../Graphics/Model.h"
#include "Component.h"

namespace Kyst {

class ModelComponent : public Drawable {
 public:
  virtual void Draw(const glm::mat4& uModel, const glm::mat4& uView, const glm::mat4& uProjection) override;

  void SetModel(std::shared_ptr<Model> model);
  Model* GetModel();

 private:
  std::shared_ptr<Model> model_;
};

}  // namespace Kyst
