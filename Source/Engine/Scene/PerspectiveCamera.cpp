#include "PerspectiveCamera.h"

#include <iostream>

#include "../Input.h"

PerspectiveCamera::PerspectiveCamera() {
  rotation_.y = pi<float>();
  rotation_.x = 0.0f;

  worldUp_ = vec3(0.0f, 1.0f, 0.0f);
  sensitivity_ = 0.001f;

  UpdateCameraVectors();
};

mat4 PerspectiveCamera::GetProjectionMatrix(int width, int height) {
  return glm::perspective(zoom_, (float)width / (float)height, 0.1f, 100.0f);
}

void PerspectiveCamera::UpdateCameraVectors() {
  vec3 front(cos(rotation_.y) * cos(rotation_.x), sin(rotation_.x), sin(rotation_.y) * cos(rotation_.x));

  front_ = normalize(front);
  right_ = normalize(cross(front_, worldUp_));
  up_ = normalize(cross(right_, front_));
}

void PerspectiveCamera::LookAt(const vec3& center) {
  vec3 front = normalize(center - position_);
  rotation_.x = asin(front.y);
  rotation_.y = acos(front.x / cos(rotation_.x)) + pi<float>();
  UpdateCameraVectors();
}

void PerspectiveCamera::Update(float deltaTime, const Input& input) {
  Camera::Update(deltaTime, input);

  Translate(deltaTime);
  Rotate();
  Zoom();
}

void PerspectiveCamera::Translate(float deltaTime) {
  float velocity = movementSpeed_ * deltaTime;

  if (movement_[CAM_FORWARD]) position_ += front_ * velocity;
  if (movement_[CAM_BACKWARD]) position_ -= front_ * velocity;
  if (movement_[CAM_LEFT]) position_ -= right_ * velocity;
  if (movement_[CAM_RIGHT]) position_ += right_ * velocity;
  if (movement_[CAM_UP]) position_ += up_ * velocity;
  if (movement_[CAM_DOWN]) position_ -= up_ * velocity;
}

void PerspectiveCamera::Rotate(bool constrainPitch) {
  rotation_.y += movement_[CAM_ROT_X] * sensitivity_;
  rotation_.x -= movement_[CAM_ROT_Y] * sensitivity_;

  if (constrainPitch) {
    rotation_.x = clamp(rotation_.x, -89.0f, 89.0f);
  }

  UpdateCameraVectors();
}

void PerspectiveCamera::Zoom() {
  zoom_ -= movement_[CAM_ZOOM] * sensitivity_ * 1e2;
  zoom_ = clamp(zoom_, .5f, 2.0f);
}
