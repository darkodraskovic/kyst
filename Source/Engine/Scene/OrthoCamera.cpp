#include "OrthoCamera.h"

namespace Kyst {

OrthoCamera::OrthoCamera() { translationSpeed_ = 500; }

mat4 OrthoCamera::GetProjectionMatrix(int width, int height) {
  vec3 center(width / 2, height / 2, 0);
  mat4 m = glm::translate(glm::mat4(1), center);
  m = glm::scale(m, {zoom_, zoom_, 0});
  m = glm::translate(m, -center);
  return glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f) * m;
}

void OrthoCamera::LookAt(const vec3& center, vec3& position, vec3& rotation) { position = center; }

void OrthoCamera::Translate(float deltaTime, const CameraMovementMap& movement, vec3& position) {
  float velocity = translationSpeed_ * deltaTime;
  if (movement.at(CAM_LEFT)) position -= right_ * velocity;
  if (movement.at(CAM_RIGHT)) position += right_ * velocity;
  if (movement.at(CAM_UP)) position += up_ * velocity;
  if (movement.at(CAM_DOWN)) position -= up_ * velocity;
}

void OrthoCamera::Rotate(const CameraMovementMap& movement, vec3& rotation, bool constrainPitch) {
  // TODO: implement
}

void OrthoCamera::Zoom(const CameraMovementMap& movement) {
  zoom_ += movement.at(CAM_FORWARD) * zoomSpeed_;
  zoom_ -= movement.at(CAM_BACKWARD) * zoomSpeed_;
  zoom_ += movement.at(CAM_ZOOM) * zoomSpeed_;
}

void OrthoCamera::Update(float deltaTime, const CameraMovementMap& movement, vec3& position, vec3& rotation) {
  Translate(deltaTime, movement, position);
  Zoom(movement);
}

}  // namespace Kyst
