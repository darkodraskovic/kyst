#include "OrthoCamera.h"

OrthoCamera::OrthoCamera() { movementSpeed_ = 500; }

mat4 OrthoCamera::GetProjectionMatrix(int width, int height) {
  vec3 center(width / 2, height / 2, 0);
  mat4 m = glm::translate(glm::mat4(1), center);
  m = glm::scale(m, {zoom_, zoom_, 0});
  m = glm::translate(m, -center);
  return glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f) * m;
}

void OrthoCamera::Update(float deltaTime, const Input* input, vec3& position, vec3& rotation) {
  Camera::Update(deltaTime, input, position, rotation);

  Translate(deltaTime, position);
  Zoom();
}

void OrthoCamera::Translate(float deltaTime, vec3& position) {
  float velocity = movementSpeed_ * deltaTime;
  if (movement_[CAM_LEFT]) position -= right_ * velocity;
  if (movement_[CAM_RIGHT]) position += right_ * velocity;
  if (movement_[CAM_UP]) position += up_ * velocity;
  if (movement_[CAM_DOWN]) position -= up_ * velocity;
}

void OrthoCamera::Rotate(vec3& rotation, bool constrainPitch) {
  // TODO: implement
}

void OrthoCamera::Zoom() {
  zoom_ += movement_[CAM_FORWARD] * zoomRate_;
  zoom_ -= movement_[CAM_BACKWARD] * zoomRate_;
  zoom_ += movement_[CAM_ZOOM] * zoomRate_;
}

void OrthoCamera::LookAt(const vec3& center, vec3& position, vec3& rotation) { position = center; }
