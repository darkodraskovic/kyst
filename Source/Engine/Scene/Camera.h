#ifndef CAMERA_H
#define CAMERA_H

#include "../Input.h"
#include "../Object.h"
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

// An abstraction to stay away from window-system specific input methods
enum CameraMovement { CAM_FORWARD, CAM_BACKWARD, CAM_LEFT, CAM_RIGHT, CAM_UP, CAM_DOWN };

using namespace glm;

// Processes input and calculates the corresponding Euler Angles, Vectors and Matrices
class Camera : public Object
{
public:
    Camera(Application* app);
    
    void Init();

    void LookAt(const vec3& center);
    mat4 GetViewMatrix();
    mat4 GetProjectionMatrix(int scrWidth, int scrHeight);
    mat4 GetOrthoMatrix(float scrWidth, int scrHeight);
    void SetOrtho(bool enabled);

    // TODO: remove this methods from Camera class
    void ProcessKeyboard(CameraMovement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void ProcessMouseScroll(float yoffset);
    void ProcessInput(Input* input, float deltaTime);
    
    vec3 position_;
    
    // Camera Attributes
    vec3 front_;
    vec3 up_;
    vec3 right_;
    vec3 worldUp_;

    // Euler Angles
    float yaw_;
    float pitch_;

    // Camera options
    float movementSpeed_;
    float mouseSensitivity_;
    float zoom_;

private:
    bool ortho_ = false;    
    void UpdateCameraVectors();
};
#endif
