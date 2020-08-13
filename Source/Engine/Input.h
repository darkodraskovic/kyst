#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

namespace MouseData
{
    extern float scrollX, scrollY;
    extern float positionX, positionY;
}

class Input
{
public:
    Input(GLFWwindow* window);

    float lastMouseX_, lastMouseY_;
    float mouseOffsetX_, mouseOffsetY_;
    bool firstMouse_ = true;

    void ProcessMouseMovement();
    bool GetKey(unsigned int key);

private:
    GLFWwindow* window_;    
};

#endif /* INPUT_H */
