#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ResourceManager.h"
#include "Entity.h"
#include "Framebuffer.h"
#include "Scene.h"
#include "Camera.h"
#include "Viewport.h"
#include "Input.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void MouseCallback(GLFWwindow* window, double posX, double posY);
void ScrollCallback(GLFWwindow* window, double offsetX, double offsetY);

class Application
{
public:
    int Init();
    void ProcessInput(float deltaTime);
    void Update();
    bool ShouldClose();
    void Terminate();
    
    static Application& Instance();

    ResourceManager resourceManager_;
  
    GLFWwindow* window_;
    ivec2 windowPosition_ = vec2(0,0);
    uvec2 windowSize_ = vec2(1152,720);

    float deltaTime_ = 0.0f;	// Time between current frame and last frame
    float lastFrame_ = 0.0f; // Time of last frame

    std::vector<std::shared_ptr<Viewport>> viewports_;
    std::shared_ptr<Camera> camera_;

    Input* input_;
    
private:
    Application();

    friend void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    friend void MouseCallback(GLFWwindow* window, double posX, double posY);
    friend void ScrollCallback(GLFWwindow* window, double offsetX, double offsetY);
    
    static bool processMouseMovement_;
    static bool processMouseScroll_;
};

#endif
