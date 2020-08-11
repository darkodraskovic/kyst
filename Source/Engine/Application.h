#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ResourceManager.h"
#include "Entity.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Viewport.h"

class Application
{
public:
    int Init();
    void InitViewport(unsigned int width, unsigned int height);
    void ProcessInput(float deltaTime);
    void Update();
    void Draw();
    void DrawScene();
    bool ShouldClose();
    void Terminate();
    void AddEntity(std::shared_ptr<Entity> entity);
    static Application& Instance();

    ResourceManager resourceManager_;
  
    GLFWwindow* window_;
    ivec2 windowPosition_ = vec2(0,0);
    uvec2 windowSize_ = vec2(1152,720);
  
    std::shared_ptr<Viewport> viewport_;
    Camera camera_;
    
    std::vector<std::shared_ptr<Entity>> entities_;

    float deltaTime_ = 0.0f;	// Time between current frame and last frame
    float lastFrame_ = 0.0f; // Time of last frame
    vec4 clearColor_ = vec4(0.2f, 0.3f, 0.3f, 1.0f);

private:
    Application();
    std::vector<std::shared_ptr<Entity>> entitiesToCreate_;
    std::vector<std::shared_ptr<Entity>> alphaEntities_;
};

#endif
