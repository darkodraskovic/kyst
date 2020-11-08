#include "OrthoCamera.h"

OrthoCamera::OrthoCamera(Application *app) : Camera(app) {
    front_ = {0, 0, -1};
    right_ = {1, 0, 0};
    movementSpeed_ = 500;
    zoom_ = 1;
}

mat4 OrthoCamera::GetProjectionMatrix(int width, int height) {
    vec3 center(width / 2, height / 2, 0);
    mat4 m = glm::translate(glm::mat4(1), center);
    m = glm::scale(m, {zoom_, zoom_, 0});
    m = glm::translate(m, -center);
    return glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f) * m;
}

void OrthoCamera::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
    float velocity = movementSpeed_ * deltaTime;
    if (direction == CAM_FORWARD)
        zoom_ += 0.02;
    if (direction == CAM_BACKWARD)
        zoom_ -= 0.02;
    if (direction == CAM_LEFT)
        position_ -= right_ * velocity;
    if (direction == CAM_RIGHT)
        position_ += right_ * velocity;
    if (direction == CAM_UP)
        position_ += up_ * velocity;
    if (direction == CAM_DOWN)
        position_ -= up_ * velocity;
}

void OrthoCamera::ProcessInput(Input* input, float deltaTime)
{
    if (input->GetKey(GLFW_KEY_W)) ProcessKeyboard(CAM_FORWARD, deltaTime);
    if (input->GetKey(GLFW_KEY_S)) ProcessKeyboard(CAM_BACKWARD, deltaTime);
    if (input->GetKey(GLFW_KEY_A)) ProcessKeyboard(CAM_LEFT, deltaTime);
    if (input->GetKey(GLFW_KEY_D)) ProcessKeyboard(CAM_RIGHT, deltaTime);
    if (input->GetKey(GLFW_KEY_E)) ProcessKeyboard(CAM_UP, deltaTime);
    if (input->GetKey(GLFW_KEY_Q)) ProcessKeyboard(CAM_DOWN, deltaTime);
}

void OrthoCamera::LookAt(const vec3& center)
{
    position_ = center;
}
