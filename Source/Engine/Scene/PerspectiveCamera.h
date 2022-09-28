#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "Camera.h"

class PerspectiveCamera : public Camera {
 public:
  PerspectiveCamera();

  virtual void LookAt(const vec3& center, vec3& position, vec3& rotation) override;
  virtual mat4 GetProjectionMatrix(int scrWidth, int scrHeight) override;

  virtual void Update(float deltaTime, const Input* input, vec3& position, vec3& rotation) override;
  virtual void Translate(float deltaTime, vec3& position) override;
  virtual void Rotate(vec3& rotation, bool constrainPitch = true) override;

  virtual void Zoom() override;

  vec3 worldUp_;
  float sensitivity_;

 private:
  void UpdateCameraVectors(const vec3& rotation);
};

#endif /* PERSPECTIVECAMERA_H */
