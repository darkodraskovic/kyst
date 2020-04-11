#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ResourceManager.h"
#include "Entity.h"
#include "Camera.h"

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 800;

class Application
{
public:
    Application();
    int Init();
    void ProcessInput(float deltaTime);
    void Render(float deltaTime);
    float GetDeltaTime();
    void Update();
    bool ShouldClose();
    void Terminate();

    ResourceManager resourceManager_;
    
    std::vector<std::shared_ptr<Entity>> entities_;
    GLFWwindow* window_;
    Camera camera_;

    float deltaTime_ = 0.0f;	// Time between current frame and last frame
    float lastFrame_ = 0.0f; // Time of last frame
    vec4 clearColor_ = vec4(0.2f, 0.3f, 0.3f, 1.0f);
};

#endif
