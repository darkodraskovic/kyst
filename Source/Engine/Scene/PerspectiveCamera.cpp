#include "PerspectiveCamera.h"

#include <iostream>

#include "../Input.h"

PerspectiveCamera::PerspectiveCamera() {
  worldUp_ = vec3(0.0f, 1.0f, 0.0f);
  sensitivity_ = 0.001f;
};

mat4 PerspectiveCamera::GetProjectionMatrix(int width, int height) {
  return glm::perspective(zoom_, (float)width / (float)height, 0.1f, 100.0f);
}

void PerspectiveCamera::UpdateCameraVectors(const vec3& rotation) {
  vec3 front(cos(rotation.y) * cos(rotation.x), sin(rotation.x), sin(rotation.y) * cos(rotation.x));

  front_ = normalize(front);
  right_ = normalize(cross(front_, worldUp_));
  up_ = normalize(cross(right_, front_));
}

void PerspectiveCamera::LookAt(const vec3& center, vec3& position, vec3& rotation) {
  vec3 front = normalize(center - position);
  rotation.x = asin(front.y);
  rotation.y = acos(front.x / cos(rotation.x)) + pi<float>();
  UpdateCameraVectors(rotation);
}

void PerspectiveCamera::Update(float deltaTime, const Input* input, vec3& position, vec3& rotation) {
  Camera::Update(deltaTime, input, position, rotation);

  Translate(deltaTime, position);
  Rotate(rotation);
  Zoom();
}

void PerspectiveCamera::Translate(float deltaTime, vec3& position) {
  float velocity = movementSpeed_ * deltaTime;

  if (movement_[CAM_FORWARD]) position += front_ * velocity;
  if (movement_[CAM_BACKWARD]) position -= front_ * velocity;
  if (movement_[CAM_LEFT]) position -= right_ * velocity;
  if (movement_[CAM_RIGHT]) position += right_ * velocity;
  if (movement_[CAM_UP]) position += up_ * velocity;
  if (movement_[CAM_DOWN]) position -= up_ * velocity;
}

void PerspectiveCamera::Rotate(vec3& rotation, bool constrainPitch) {
  rotation.y += movement_[CAM_ROT_X] * sensitivity_;
  rotation.x -= movement_[CAM_ROT_Y] * sensitivity_;

  if (constrainPitch) {
    rotation.x = clamp(rotation.x, -89.0f, 89.0f);
  }

  UpdateCameraVectors(rotation);
}

void PerspectiveCamera::Zoom() {
  zoom_ -= movement_[CAM_ZOOM] * sensitivity_ * 1e2;
  zoom_ = clamp(zoom_, .5f, 2.0f);
}
