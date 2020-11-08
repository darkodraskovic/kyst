#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "Camera.h"

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(Application* app);

    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void ProcessMouseScroll(float yoffset);
    virtual void LookAt(const vec3& center) override;

    virtual mat4 GetProjectionMatrix(int scrWidth, int scrHeight) override;
    
    virtual void ProcessKeyboard(CameraMovement direction, float deltaTime) override;
    virtual void ProcessInput(Input* input, float deltaTime) override;
    
    vec3 worldUp_;

    float yaw_;
    float pitch_;

    float mouseSensitivity_;

private:
    void UpdateCameraVectors();
};


#endif /* PERSPECTIVECAMERA_H */
