#pragma once

#include "Camera.h"

namespace Kyst {

class PerspectiveCamera : public Camera {
 public:
  virtual mat4 GetProjectionMatrix(int scrWidth, int scrHeight) override;
  virtual void LookAt(const vec3& center, vec3& position, vec3& rotation) override;

  virtual void Translate(float deltaTime, const CameraMovementMap& movement, vec3& position) override;
  virtual void Rotate(const CameraMovementMap& movement, vec3& rotation, bool constrainPitch = true) override;
  virtual void Zoom(const CameraMovementMap& movement) override;
  virtual void Update(float deltaTime, const CameraMovementMap& movement, vec3& position, vec3& rotation) override;

 private:
  void UpdateCameraVectors(const vec3& rotation);
};

}  // namespace Kyst
