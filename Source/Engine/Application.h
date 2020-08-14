#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ResourceManager.h"
#include "Camera.h"
#include "Input.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void MouseCallback(GLFWwindow* window, double posX, double posY);
void ScrollCallback(GLFWwindow* window, double offsetX, double offsetY);

class Viewport;

class Application
{
public:
    int Init();
    void ProcessInput(float deltaTime);
    void Update();
    bool ShouldClose();
    void Terminate();
    Input* GetInput();
    
    static Application& Instance();

    ResourceManager resourceManager_;
  
    GLFWwindow* window_;
    ivec2 windowPosition_ = vec2(0,0);
    uvec2 windowSize_ = vec2(1152,720);

    float deltaTime_ = 0.0f;
    float lastFrame_ = 0.0f;

    void AddViewport(std::shared_ptr<Viewport> viewport);
    std::shared_ptr<Camera> camera_;

private:
    Application();
    Input* input_;
    
    friend void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    friend void MouseCallback(GLFWwindow* window, double posX, double posY);
    friend void ScrollCallback(GLFWwindow* window, double offsetX, double offsetY);

    std::vector<std::shared_ptr<Viewport>> viewports_;    
    static bool processMouseMovement_;
    static bool processMouseScroll_;
};

#endif
