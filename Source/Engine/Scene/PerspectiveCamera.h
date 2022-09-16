#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "Camera.h"

class PerspectiveCamera : public Camera {
 public:
  PerspectiveCamera();

  virtual void LookAt(const vec3& center) override;
  virtual mat4 GetProjectionMatrix(int scrWidth, int scrHeight) override;

  virtual void Update(float deltaTime, const Input& input) override;
  virtual void Translate(float deltaTime) override;
  void Rotate(bool constrainPitch = true);

  virtual void Zoom() override;

  vec3 worldUp_;
  float sensitivity_;

 private:
  void UpdateCameraVectors();
};

#endif /* PERSPECTIVECAMERA_H */
