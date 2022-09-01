#include "PerspectiveCamera.h"

#include <iostream>

#include "../Input.h"

PerspectiveCamera::PerspectiveCamera() {
  yaw_ = pi<float>();
  pitch_ = 0.0f;

  worldUp_ = vec3(0.0f, 1.0f, 0.0f);
  sensitivity_ = 0.001f;

  UpdateCameraVectors();
};

mat4 PerspectiveCamera::GetProjectionMatrix(int width, int height) {
  return glm::perspective(zoom_, (float)width / (float)height, 0.1f, 100.0f);
}

void PerspectiveCamera::UpdateCameraVectors() {
  vec3 front(cos(yaw_) * cos(pitch_), sin(pitch_), sin(yaw_) * cos(pitch_));

  front_ = normalize(front);
  right_ = normalize(cross(front_, worldUp_));
  up_ = normalize(cross(right_, front_));
}

void PerspectiveCamera::LookAt(const vec3& center) {
  vec3 front = normalize(center - position_);
  pitch_ = asin(front.y);
  yaw_ = acos(front.x / cos(pitch_)) + pi<float>();
  UpdateCameraVectors();
}

void PerspectiveCamera::Update(float deltaTime, const Input& input) {
  if (input.GetKey(GLFW_KEY_W)) Translate(CAM_FORWARD, deltaTime);
  if (input.GetKey(GLFW_KEY_S)) Translate(CAM_BACKWARD, deltaTime);
  if (input.GetKey(GLFW_KEY_A)) Translate(CAM_LEFT, deltaTime);
  if (input.GetKey(GLFW_KEY_D)) Translate(CAM_RIGHT, deltaTime);
  if (input.GetKey(GLFW_KEY_E)) Translate(CAM_UP, deltaTime);
  if (input.GetKey(GLFW_KEY_Q)) Translate(CAM_DOWN, deltaTime);

  Rotate(Input::mouseData_.moveX_, Input::mouseData_.moveY_);
  if (Input::mouseData_.scrolled_) Zoom(Input::mouseData_.scrollY_);
}

void PerspectiveCamera::Translate(CameraMovement direction, float deltaTime) {
  float velocity = movementSpeed_ * deltaTime;
  if (direction == CAM_FORWARD) position_ += front_ * velocity;
  if (direction == CAM_BACKWARD) position_ -= front_ * velocity;
  if (direction == CAM_LEFT) position_ -= right_ * velocity;
  if (direction == CAM_RIGHT) position_ += right_ * velocity;
  if (direction == CAM_UP) position_ += up_ * velocity;
  if (direction == CAM_DOWN) position_ -= up_ * velocity;
}

void PerspectiveCamera::Rotate(float xoffset, float yoffset, bool constrainPitch) {
  yaw_ += xoffset * sensitivity_;
  pitch_ -= yoffset * sensitivity_;

  if (constrainPitch) {
    pitch_ = clamp(pitch_, -89.0f, 89.0f);
  }

  UpdateCameraVectors();
}

void PerspectiveCamera::Zoom(float yoffset) {
  zoom_ -= yoffset * sensitivity_ * 1e2;
  zoom_ = clamp(zoom_, .5f, 2.0f);
}
