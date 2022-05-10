#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "Camera.h"

class PerspectiveCamera : public Camera {
 public:
  PerspectiveCamera(Application* app);

  void Zoom(float yoffset);
  virtual void LookAt(const vec3& center) override;

  virtual mat4 GetProjectionMatrix(int scrWidth, int scrHeight) override;

  virtual void Update(float deltaTime) override;
  virtual void Translate(CameraMovement direction, float deltaTime) override;
  void Rotate(float xoffset, float yoffset, bool constrainPitch = true);

  vec3 worldUp_;

  float yaw_;
  float pitch_;

  float sensitivity_;

 private:
  void UpdateCameraVectors();
};

#endif /* PERSPECTIVECAMERA_H */
