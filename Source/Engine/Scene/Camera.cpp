#include "Camera.h"
#include <glm/ext/scalar_constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

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
    return lookAt(position_, position_ + front_, up_);
}

// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
mat4 Camera::GetProjectionMatrix(int scrWidth, int scrHeight)
{
    return perspective(
        zoom_,
        (float)scrWidth/(float)scrHeight, 0.1f, 100.0f);
}
    
// Processes input received from any keyboard-like input system.
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

// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    yaw_   += xoffset * mouseSensitivity_;
    pitch_ -= yoffset * mouseSensitivity_;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        pitch_ = clamp(pitch_, -89.0f, 89.0f);
    }

    // Update front_, right_ and up_ Vectors using the updated Euler angles
    UpdateCameraVectors();
}

// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
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

    ProcessMouseMovement(input->mouseOffsetX_, input->mouseOffsetY_);
    ProcessMouseScroll(MouseData::scrollY);
}

// Calculates the front vector from the Camera's (updated) Euler Angles
void Camera::UpdateCameraVectors()
{
    // Calculate the new front_ vector
    vec3 front;
    front.x = cos(yaw_) * cos(pitch_);
    front.y = sin(pitch_);
    front.z = sin(yaw_) * cos(pitch_);
    front_ = normalize(front);
    // Also re-calculate the right_ and up_ vector
    right_ = normalize(cross(front_, worldUp_));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up_    = normalize(cross(right_, front_));
}

void Camera::LookAt(const vec3& center)
{
    vec3 front = normalize(center - position_);
    pitch_ = asin(front.y);
    yaw_ = acos(front.x/cos(pitch_)) + pi<float>();
    UpdateCameraVectors();
}
