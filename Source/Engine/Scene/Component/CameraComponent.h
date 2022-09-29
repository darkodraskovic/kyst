#pragma once

#include <memory>

#include "../Camera.h"
#include "Component.h"

namespace Kyst {

class CameraComponent : public Updatable {
 public:
  CameraComponent();

  virtual void Update(float deltaTime) override;

  void SetCamera(std::shared_ptr<Camera> camera);
  Camera* GetCamera();

 private:
  std::shared_ptr<Camera> camera_;
  CameraMovementMap movement_;
};

}  // namespace Kyst
