#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <map>

namespace Kyst {

enum CameraMovement { CAM_FORWARD, CAM_BACKWARD, CAM_LEFT, CAM_RIGHT, CAM_UP, CAM_DOWN, CAM_ROT_X, CAM_ROT_Y, CAM_ZOOM };

typedef std::map<CameraMovement, float> CameraMovementMap;

using namespace glm;

class Camera {
 public:
  Camera();

  mat4 GetViewMatrix(const vec3& position);

  void SetCameraVectors(const vec3& rotation);

  mat4 GetProjectionMatrix(int scrWidth, int scrHeight);
  void LookAt(const vec3& center, vec3& position, vec3& rotation);

  void SetPerspective(bool perspective);
  bool GetPerspective();

  vec3 right_{1, 0, 0};
  vec3 up_{0, 1, 0};
  vec3 front_{0, 0, -1};
  vec3 worldUp_{0.0f, 1.0f, 0.0f};

  float zoom_{1};

 private:
  mat4 (Camera::*GetProjectionMatrixPtr)(int scrWidth, int scrHeight);
  mat4 GetProjectionMatrixOrtho(int width, int height);
  mat4 GetProjectionMatrixPerspective(int width, int height);

  void (Camera::*LookAtPtr)(const vec3& center, vec3& position, vec3& rotation);
  void LookAtOrtho(const vec3& center, vec3& position, vec3& rotation);
  void LookAtPerspective(const vec3& center, vec3& position, vec3& rotation);

  bool perspective_ = true;
};

}  // namespace Kyst
