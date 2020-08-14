#include "Input.h"

namespace MouseData
{
    float scrollX = 0, scrollY = 0;
    float positionX = 0, positionY = 0;
}

Input::Input(GLFWwindow *window)
    : window_(window)
{}

void Input::ProcessMouseMovement()
{
    using namespace MouseData;
    if (firstMouse_) {
        lastMouseX_ = positionX;
        lastMouseY_ = positionY;
        firstMouse_ = false;
    }

    mouseOffsetX_ = positionX - lastMouseX_;
    mouseOffsetY_ = positionY - lastMouseY_;
    lastMouseX_ = positionX;
    lastMouseY_ = positionY;
}

bool Input::GetKey(unsigned int key)
{
    return glfwGetKey(window_, key) == GLFW_PRESS;
}
