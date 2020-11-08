#ifndef INPUT_H
#define INPUT_H

#include "Core.h"

namespace MouseData
{
    extern float scrollX, scrollY;
    extern float positionX, positionY;
}

class Input
{
public:
    Input(GLFWwindow* window);

    float lastMouseX_{0}, lastMouseY_{0};
    float mouseOffsetX_{0}, mouseOffsetY_{0};

    void ProcessMouseMovement();
    bool GetKey(unsigned int key);

private:
    GLFWwindow* window_;  
};

#endif /* INPUT_H */
