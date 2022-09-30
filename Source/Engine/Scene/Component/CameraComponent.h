#pragma once

#include <memory>

#include "../Camera.h"
#include "Component.h"

namespace Kyst {

class CameraComponent : public Updatable {
 public:
  CameraComponent();

  virtual void Update(float deltaTime) override;
  void UpdateMovementMap();

  void SetCamera(std::shared_ptr<Camera> camera);
  Camera* GetCamera();

  float translationSpeed_{5.0};
  float rotationSpeed_{0.001f};
  float zoomSpeed_ = .04f;

 private:
  void Translate(float deltaTime);
  void Rotate(bool constrainPitch = true);
  void Zoom();

  std::shared_ptr<Camera> camera_;
  CameraMovementMap movement_;
};

}  // namespace Kyst
