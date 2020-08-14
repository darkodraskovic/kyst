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
    Application();
        
    int Init();
    void ProcessInput(float deltaTime);
    void Update();
    bool ShouldClose();
    void Terminate();
    Input* GetInput();

    static void SetWindowSize(const uvec2& size);
    static const uvec2& GetWindowSize();
    static void SetWindowPosition(const ivec2& size);
    static const ivec2& GetWindowPosition();

    ResourceManager resourceManager_;
  
    GLFWwindow* window_;

    float deltaTime_ = 0.0f;
    float lastFrame_ = 0.0f;

    Viewport* AddViewport();
    void AddViewport(std::shared_ptr<Viewport> viewport);
    std::shared_ptr<Camera> camera_;

private:
    friend void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    friend void MouseCallback(GLFWwindow* window, double posX, double posY);
    friend void ScrollCallback(GLFWwindow* window, double offsetX, double offsetY);

    Input* input_;    
    std::vector<std::shared_ptr<Viewport>> viewports_;
    
    static bool processMouseMovement_;
    static bool processMouseScroll_;
    static uvec2 windowSize_;
    static ivec2 windowPosition_;
};

#endif
