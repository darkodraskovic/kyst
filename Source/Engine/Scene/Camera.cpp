#include "Camera.h"

#include <iostream>

namespace Kyst {
Camera::Camera() { SetPerspective(true); }

void Camera::SetPerspective(bool perspective) {
  if (perspective) {
    GetProjectionMatrixPtr = &Camera::GetProjectionMatrixPerspective;
    LookAtPtr = &Camera::LookAtPerspective;
    perspective_ = true;
  } else {
    GetProjectionMatrixPtr = &Camera::GetProjectionMatrixOrtho;
    LookAtPtr = &Camera::LookAtOrtho;
    perspective_ = false;
  }
}

bool Camera::GetPerspective() { return perspective_; }

mat4 Camera::GetViewMatrix(const vec3& position) { return glm::lookAt(position, position + front_, up_); }

mat4 Camera::GetProjectionMatrixOrtho(int width, int height) {
  vec3 center(width / 2, height / 2, 0);
  mat4 m = glm::translate(glm::mat4(1), center);
  m = glm::scale(m, {zoom_, zoom_, 0});
  m = glm::translate(m, -center);
  return glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f) * m;
}

mat4 Camera::GetProjectionMatrix(int scrWidth, int scrHeight) {
  return ((*this).*GetProjectionMatrixPtr)(scrWidth, scrHeight);
};

mat4 Camera::GetProjectionMatrixPerspective(int width, int height) {
  return glm::perspective(zoom_, (float)width / (float)height, 0.1f, 100.0f);
}

void Camera::LookAtOrtho(const vec3& center, vec3& position, vec3& rotation) { position = center; }

void Camera::LookAtPerspective(const vec3& center, vec3& position, vec3& rotation) {
  vec3 front = normalize(center - position);
  rotation.x = asin(front.y);
  rotation.y = acos(front.x / cos(rotation.x)) + pi<float>();
  SetCameraVectors(rotation);
}
void Camera::LookAt(const vec3& center, vec3& position, vec3& rotation) {
  return ((*this).*LookAtPtr)(center, position, rotation);
};

void Camera::SetCameraVectors(const vec3& rotation) {
  vec3 front(cos(rotation.y) * cos(rotation.x), sin(rotation.x), sin(rotation.y) * cos(rotation.x));

  front_ = normalize(front);
  right_ = normalize(cross(front_, worldUp_));
  up_ = normalize(cross(right_, front_));
}

}  // namespace Kyst
