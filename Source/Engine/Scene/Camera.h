#ifndef CAMERA_H
#define CAMERA_H

#include <glm/gtc/matrix_transform.hpp>
#include <map>

#include "../Input.h"

enum CameraMovement { CAM_FORWARD, CAM_BACKWARD, CAM_LEFT, CAM_RIGHT, CAM_UP, CAM_DOWN, CAM_ROT_X, CAM_ROT_Y, CAM_ZOOM };

using namespace glm;

class Camera {
 public:
  Camera();

  mat4 GetViewMatrix(const vec3& position);
  virtual mat4 GetProjectionMatrix(int scrWidth, int scrHeight) = 0;

  virtual void LookAt(const vec3& center, vec3& position, vec3& rotation) = 0;
  // TODO: move this method from Camera to Entity
  virtual void Translate(float deltaTime, vec3& position) = 0;
  virtual void Rotate(vec3& rotation, bool constrainPitch = true) = 0;
  virtual void HandleInput(const Input* input);
  virtual void Update(float deltaTime, const Input* input, vec3& position, vec3& rotation);
  virtual void Zoom() = 0;

  vec3 right_{1, 0, 0};
  vec3 up_{0, 1, 0};
  vec3 front_{0, 0, -1};

  float zoom_{1};

  float movementSpeed_{5.0};

 protected:
  std::map<CameraMovement, float> movement_;
};
#endif
