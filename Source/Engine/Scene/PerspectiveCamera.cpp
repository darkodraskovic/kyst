#include "PerspectiveCamera.h"

#include <iostream>

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

void PerspectiveCamera::Translate(float deltaTime, const CameraMovementMap& movement, vec3& position) {
  float velocity = translationSpeed_ * deltaTime;

  if (movement.at(CAM_FORWARD)) position += front_ * velocity;
  if (movement.at(CAM_BACKWARD)) position -= front_ * velocity;
  if (movement.at(CAM_LEFT)) position -= right_ * velocity;
  if (movement.at(CAM_RIGHT)) position += right_ * velocity;
  if (movement.at(CAM_UP)) position += up_ * velocity;
  if (movement.at(CAM_DOWN)) position -= up_ * velocity;
}

void PerspectiveCamera::Rotate(const CameraMovementMap& movement, vec3& rotation, bool constrainPitch) {
  rotation.y += movement.at(CAM_ROT_X) * rotationSpeed_;
  rotation.x -= movement.at(CAM_ROT_Y) * rotationSpeed_;

  if (constrainPitch) {
    rotation.x = clamp(rotation.x, -89.0f, 89.0f);
  }

  UpdateCameraVectors(rotation);
}

void PerspectiveCamera::Zoom(const CameraMovementMap& movement) {
  zoom_ -= movement.at(CAM_ZOOM) * zoomSpeed_;
  zoom_ = clamp(zoom_, .5f, 2.0f);
}

void PerspectiveCamera::Update(float deltaTime, const CameraMovementMap& movement, vec3& position, vec3& rotation) {
  Translate(deltaTime, movement, position);
  Rotate(movement, rotation);
  Zoom(movement);
}
