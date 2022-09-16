#ifndef ORTHOCAMERA_H
#define ORTHOCAMERA_H

#include "Camera.h"

class Viewport;
class OrthoCamera : public Camera {
 public:
  OrthoCamera();

  virtual mat4 GetProjectionMatrix(int scrWidth, int scrHeight) override;
  virtual void LookAt(const vec3& center) override;

  virtual void Update(float deltaTime, const Input& input) override;
  virtual void Translate(float deltaTime) override;
  virtual void Zoom() override;

  float zoomRate_ = .02f;
};

#endif /* ORTHOCAMERA_H */
