#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <map>

namespace Kyst {

enum CameraMovement { CAM_FORWARD, CAM_BACKWARD, CAM_LEFT, CAM_RIGHT, CAM_UP, CAM_DOWN, CAM_ROT_X, CAM_ROT_Y, CAM_ZOOM };

typedef std::map<CameraMovement, float> CameraMovementMap;

using namespace glm;

class Camera {
 public:
  mat4 GetViewMatrix(const vec3& position);

  virtual mat4 GetProjectionMatrix(int scrWidth, int scrHeight) = 0;
  virtual void LookAt(const vec3& center, vec3& position, vec3& rotation) = 0;
  // TODO: move this method from Camera to Entity

  virtual void Translate(float deltaTime, const CameraMovementMap& map, vec3& position) = 0;
  virtual void Rotate(const CameraMovementMap& movement, vec3& rotation, bool constrainPitch = true) = 0;
  virtual void Zoom(const CameraMovementMap& movement) = 0;
  virtual void Update(float deltaTime, const CameraMovementMap& movement, vec3& position, vec3& rotation) = 0;

  vec3 right_{1, 0, 0};
  vec3 up_{0, 1, 0};
  vec3 front_{0, 0, -1};
  vec3 worldUp_{0.0f, 1.0f, 0.0f};

  float zoom_{1};

  float translationSpeed_{5.0};
  float rotationSpeed_{0.001f};
  float zoomSpeed_ = .04f;
};

}  // namespace Kyst
