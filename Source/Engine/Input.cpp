#include "Input.h"

namespace MouseData
{
    float scrollX = 0, scrollY = 0;
    float positionX = 0, positionY = 0;
    bool scrolled = false;
}

Input::Input(GLFWwindow *window)
    : window_(window)
{}

void Input::Process(){
    if(glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window_, true);
    }

    ProcessMouseMovement();
};

void Input::Reset(){
    MouseData::scrolled = false;
};

void Input::ProcessMouseMovement()
{
    using namespace MouseData;

    mouseOffsetX_ = positionX - lastMouseX_;
    mouseOffsetY_ = positionY - lastMouseY_;
    lastMouseX_ = positionX;
    lastMouseY_ = positionY;
}

bool Input::GetKey(unsigned int key)
{
    return glfwGetKey(window_, key) == GLFW_PRESS;
}
