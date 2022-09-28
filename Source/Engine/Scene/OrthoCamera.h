#ifndef ORTHOCAMERA_H
#define ORTHOCAMERA_H

#include "Camera.h"

class Viewport;
class OrthoCamera : public Camera {
 public:
  OrthoCamera();

  virtual mat4 GetProjectionMatrix(int scrWidth, int scrHeight) override;
  virtual void LookAt(const vec3& center, vec3& position, vec3& rotation) override;

  virtual void Update(float deltaTime, const Input* input, vec3& position, vec3& rotation) override;
  virtual void Translate(float deltaTime, vec3& position) override;
  virtual void Rotate(vec3& rotation, bool constrainPitch = true) override;
  virtual void Zoom() override;

  float zoomRate_ = .02f;
};

#endif /* ORTHOCAMERA_H */
