#ifndef CAMERA_H
#define CAMERA_H

#include "Input.h"
#include <glm/ext/scalar_constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

// An abstraction to stay away from window-system specific input methods
enum CameraMovement { CAM_FORWARD, CAM_BACKWARD, CAM_LEFT, CAM_RIGHT, CAM_UP, CAM_DOWN };

namespace CameraDefaults
{
    const float YAW         = glm::pi<float>()/2;
    const float PITCH       = 0.0f;
    const float SPEED       = 5.0f;
    const float SENSITIVITY = 0.001f;
    const float ZOOM        = glm::pi<float>()/4;
}

using namespace glm;
using namespace CameraDefaults;

// Processes input and calculates the corresponding Euler Angles, Vectors and Matrices
class Camera
{
public:
    Camera(vec3 position = vec3(0.0f, 0.0f, 0.0f),
           vec3 up = vec3(0.0f, 1.0f, 0.0f),
           float yaw = YAW, float pitch = PITCH);

    void LookAt(const vec3& center);
    mat4 GetViewMatrix();
    mat4 GetProjectionMatrix(int scrWidth, int scrHeight);

    // TODO: remove this methods from Camera class
    void ProcessKeyboard(CameraMovement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void ProcessMouseScroll(float yoffset);
    void ProcessInput(Input* input, float deltaTime);
    
    // Camera Attributes
    vec3 position_;
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
    void UpdateCameraVectors();
};
#endif
