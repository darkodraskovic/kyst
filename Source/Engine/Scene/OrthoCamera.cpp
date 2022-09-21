#include "OrthoCamera.h"

OrthoCamera::OrthoCamera() { movementSpeed_ = 500; }

mat4 OrthoCamera::GetProjectionMatrix(int width, int height) {
  vec3 center(width / 2, height / 2, 0);
  mat4 m = glm::translate(glm::mat4(1), center);
  m = glm::scale(m, {zoom_, zoom_, 0});
  m = glm::translate(m, -center);
  return glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f) * m;
}

void OrthoCamera::Update(float deltaTime, const Input* input) {
  Camera::Update(deltaTime, input);

  Translate(deltaTime);
  Zoom();
}

void OrthoCamera::Translate(float deltaTime) {
  float velocity = movementSpeed_ * deltaTime;
  if (movement_[CAM_LEFT]) position_ -= right_ * velocity;
  if (movement_[CAM_RIGHT]) position_ += right_ * velocity;
  if (movement_[CAM_UP]) position_ += up_ * velocity;
  if (movement_[CAM_DOWN]) position_ -= up_ * velocity;
}

void OrthoCamera::Zoom() {
  zoom_ += movement_[CAM_FORWARD] * zoomRate_;
  zoom_ -= movement_[CAM_BACKWARD] * zoomRate_;
  zoom_ += movement_[CAM_ZOOM] * zoomRate_;
}

void OrthoCamera::LookAt(const vec3& center) { position_ = center; }
