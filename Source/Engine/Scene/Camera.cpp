#include "Camera.h"

#include <iostream>

Camera::Camera() {
  for (int key = CAM_FORWARD; key != CAM_ZOOM; key++) {
    CameraMovement movement = static_cast<CameraMovement>(key);
    movement_.insert({movement, 0});
  }
}

void Camera::HandleInput(const Input* input) {
  // reset movement map
  for (int key = CAM_FORWARD; key != CAM_ZOOM; key++) {
    CameraMovement movement = static_cast<CameraMovement>(key);
    movement_[movement] = 0;
  }

  movement_[CAM_FORWARD] = input->GetKey(GLFW_KEY_W);
  movement_[CAM_BACKWARD] = input->GetKey(GLFW_KEY_S);
  movement_[CAM_LEFT] = input->GetKey(GLFW_KEY_A);
  movement_[CAM_RIGHT] = input->GetKey(GLFW_KEY_D);
  movement_[CAM_UP] = input->GetKey(GLFW_KEY_E);
  movement_[CAM_DOWN] = input->GetKey(GLFW_KEY_Q);

  movement_[CAM_ROT_X] = Input::mouseData_.moveX_;
  movement_[CAM_ROT_Y] = Input::mouseData_.moveY_;

  movement_[CAM_ZOOM] = Input::mouseData_.scrollY_;
}

void Camera::Update(float deltaTime, const Input* input, vec3& position, vec3& rotation) { HandleInput(input); }

mat4 Camera::GetViewMatrix(const vec3& position) { return glm::lookAt(position, position + front_, up_); }
