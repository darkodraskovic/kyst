#include "PerspectiveCamera.h"
#include "Source/Engine/Input.h"

PerspectiveCamera::PerspectiveCamera(Application* app) : Camera(app) {
    yaw_ = glm::pi<float>();
    pitch_ = 0.0f;

    worldUp_ = vec3(0.0f, 1.0f, 0.0f);;

    mouseSensitivity_ = 0.001f;

    UpdateCameraVectors();
};

mat4 PerspectiveCamera::GetProjectionMatrix(int width, int height) {
    return glm::perspective(zoom_, (float)width / (float)height, 0.1f, 100.0f);
}

// Update front_, right_ and up_ Vectors using the updated Euler angles (yaw_ and pitch_)


void PerspectiveCamera::UpdateCameraVectors()
{
    vec3 front;
    front.x = cos(yaw_) * cos(pitch_);
    front.y = sin(pitch_);
    front.z = sin(yaw_) * cos(pitch_);
    front_ = normalize(front);
    right_ = normalize(cross(front_, worldUp_));
    up_ = normalize(cross(right_, front_));
}

void PerspectiveCamera::LookAt(const vec3& center)
{
    vec3 front = normalize(center - position_);
    pitch_ = asin(front.y);
    yaw_ = acos(front.x/cos(pitch_)) + pi<float>();
    UpdateCameraVectors();
}

// Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void PerspectiveCamera::ProcessKeyboard(CameraMovement direction, float deltaTime)
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

void PerspectiveCamera::ProcessInput(Input* input, float deltaTime)
{
    if (input->GetKey(GLFW_KEY_W)) ProcessKeyboard(CAM_FORWARD, deltaTime);
    if (input->GetKey(GLFW_KEY_S)) ProcessKeyboard(CAM_BACKWARD, deltaTime);
    if (input->GetKey(GLFW_KEY_A)) ProcessKeyboard(CAM_LEFT, deltaTime);
    if (input->GetKey(GLFW_KEY_D)) ProcessKeyboard(CAM_RIGHT, deltaTime);
    if (input->GetKey(GLFW_KEY_E)) ProcessKeyboard(CAM_UP, deltaTime);
    if (input->GetKey(GLFW_KEY_Q)) ProcessKeyboard(CAM_DOWN, deltaTime);

    ProcessMouseMovement(input->mouseOffsetX_, input->mouseOffsetY_);
    if (MouseData::scrolled) ProcessMouseScroll(MouseData::scrollY);
}
void PerspectiveCamera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    yaw_   += xoffset * mouseSensitivity_;
    pitch_ -= yoffset * mouseSensitivity_;

    if (constrainPitch) {
        pitch_ = clamp(pitch_, -89.0f, 89.0f);
    }

    UpdateCameraVectors();
}

void PerspectiveCamera::ProcessMouseScroll(float yoffset)
{
    zoom_ -= yoffset * mouseSensitivity_ * 10;
    zoom_ = clamp(zoom_, 1.0f, 45.0f);
}
