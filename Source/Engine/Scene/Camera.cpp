#include <iostream>

#include "Camera.h"
#include "../Application.h"

vec3 center;

// Constructor with vectors
Camera::Camera(Application* app) : Object(app)
{
    position_ = vec3(0.0f, 0.0f, 0.0f);
    
    yaw_ = glm::pi<float>();
    pitch_ = 0.0f;
    
    up_ = vec3(0.0f, 1.0f, 0.0f);
    worldUp_ = up_;
    front_ = vec3(0.0f, 0.0f, -1.0f);
    
    movementSpeed_ = 5.0f;
    mouseSensitivity_ = 0.001f;
    zoom_ = 1.0f;
    
    UpdateCameraVectors();
}

void Camera::SetOrtho(bool enabled) {
    ortho_ = true;
    front_ = {0, 0, -1};
    right_ = {1, 0, 0};
    movementSpeed_ = 500;
    zoom_ = 1;
    center = vec3(app_->GetWindowSize().x / 2, app_->GetWindowSize().y / 2, 0);
    // center = vec3{1152,720, 0} / 2.0f;
}

// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(position_, position_ + front_, up_);
}

mat4 Camera::GetProjectionMatrix(int scrWidth, int scrHeight)
{
    if (ortho_) {
        mat4 m = glm::translate(glm::mat4(1), center);
        m = glm::scale(m, {zoom_, zoom_, 0});
        m = glm::translate(m, -center);
        return glm::ortho(0.0f, (float)scrWidth, 0.0f, (float)scrHeight, -1.0f, 1.0f) * m;
    }
    return glm::perspective(zoom_, (float)scrWidth/(float)scrHeight, 0.1f, 100.0f);
}
    
// Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
    float velocity = movementSpeed_ * deltaTime;
    if (ortho_) {
        if (direction == CAM_FORWARD)
            zoom_ += 0.02;
        if (direction == CAM_BACKWARD)
            zoom_ -= 0.02;
    } else {
        if (direction == CAM_FORWARD)
            position_ += front_ * velocity;
        if (direction == CAM_BACKWARD)
            position_ -= front_ * velocity;
    }
    
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

    if (!ortho_) ProcessMouseMovement(input->mouseOffsetX_, input->mouseOffsetY_);
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
