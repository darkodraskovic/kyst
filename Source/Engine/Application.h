#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ResourceManager.h"
#include "Entity.h"
#include "Framebuffer.h"
#include "Scene.h"
#include "Camera.h"
#include "Viewport.h"

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

    std::shared_ptr<Camera> camera_;
    
    float deltaTime_ = 0.0f;	// Time between current frame and last frame
    float lastFrame_ = 0.0f; // Time of last frame

    std::vector<std::shared_ptr<Viewport>> viewports_;
    
private:
    Application();
};

#endif
