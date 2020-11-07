#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

#include "Camera.h"

// Constructor with vectors
Camera::Camera(vec3 position, vec3 up, float yaw, float pitch) :
    front_(vec3(0.0f, 0.0f, -1.0f)),
    movementSpeed_(SPEED),
    mouseSensitivity_(SENSITIVITY),
    zoom_(ZOOM)
{
    position_ = position;
    worldUp_ = up;
    yaw_ = yaw;
    pitch_ = pitch;
    UpdateCameraVectors();
}

// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(position_, position_ + front_, up_);
}

mat4 Camera::GetProjectionMatrix(int scrWidth, int scrHeight)
{
    if (ortho_) return glm::ortho(0.0f, (float)scrWidth, 0.0f, (float)scrHeight, -1.0f, 1.0f);
    return glm::perspective(zoom_, (float)scrWidth/(float)scrHeight, 0.1f, 100.0f);
}
    
// Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
    float velocity = movementSpeed_ * deltaTime;
    if (direction == CAM_FORWARD)
        position_ += front_ * velocity;
    if (direction == CAM_BACKWARD)
        position_ -= front_ * velocity;
    if (direction == CAM_LEFT)
        position_ -= right_ * velocity;
    if (direction == CAM_RIGHT)
        position_ += right_ * velocity;
    if (direction == CAM_UP)
        position_ += up_ * velocity;
    if (direction == CAM_DOWN)
        position_ -= up_ * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    yaw_   += xoffset * mouseSensitivity_;
    pitch_ -= yoffset * mouseSensitivity_;

    if (constrainPitch) {
        pitch_ = clamp(pitch_, -89.0f, 89.0f);
    }

    UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    zoom_ -= yoffset * mouseSensitivity_;
    zoom_ = clamp(zoom_, 1.0f, 45.0f);
}

void Camera::ProcessInput(Input* input, float deltaTime)
{
    if (input->GetKey(GLFW_KEY_W)) ProcessKeyboard(CAM_FORWARD, deltaTime);
    if (input->GetKey(GLFW_KEY_S)) ProcessKeyboard(CAM_BACKWARD, deltaTime);
    if (input->GetKey(GLFW_KEY_A)) ProcessKeyboard(CAM_LEFT, deltaTime);
    if (input->GetKey(GLFW_KEY_D)) ProcessKeyboard(CAM_RIGHT, deltaTime);
    if (input->GetKey(GLFW_KEY_E)) ProcessKeyboard(CAM_UP, deltaTime);
    if (input->GetKey(GLFW_KEY_Q)) ProcessKeyboard(CAM_DOWN, deltaTime);

    if (processMouseMovement_) ProcessMouseMovement(input->mouseOffsetX_, input->mouseOffsetY_);
    ProcessMouseScroll(MouseData::scrollY);
}

// Update front_, right_ and up_ Vectors using the updated Euler angles (yaw_ and pitch_)
void Camera::UpdateCameraVectors()
{
    vec3 front;
    front.x = cos(yaw_) * cos(pitch_);
    front.y = sin(pitch_);
    front.z = sin(yaw_) * cos(pitch_);
    front_ = normalize(front);
    right_ = normalize(cross(front_, worldUp_));
    up_ = normalize(cross(right_, front_));
}

void Camera::LookAt(const vec3& center)
{
    vec3 front = normalize(center - position_);
    pitch_ = asin(front.y);
    yaw_ = acos(front.x/cos(pitch_)) + pi<float>();
    UpdateCameraVectors();
}
