#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "Application.h"
#include "Mesh.h"
#include "Framebuffer.h"

class Scene;

class Viewport
{
public:
    Viewport();    
    Viewport(unsigned int width, unsigned int height);
    Viewport(std::shared_ptr<Scene> scene_, unsigned int width, unsigned int height);
    Scene* GetScene();
    void Init(unsigned int width, unsigned int height);
    void Update(float deltaTime);
    void Render();
    void Draw();
    void AddEffect(const char* fragmentPath);

    vec3 position_ = vec3(0.f);

    static const std::string vertexPath_;
    static const std::string fragmentPath_;

private:
    void GenBuffers(float width, float height);
    void GenQuad(float width, float height);

    Application* application_;

    unsigned int width_;
    unsigned int height_;
    
    std::shared_ptr<Mesh> quad_;
    std::shared_ptr<Shader> shader_;
    unsigned int texture_;
        
    std::shared_ptr<Scene> scene_;

    std::shared_ptr<Framebuffer> frontbuffer_;
    std::shared_ptr<Framebuffer> backbuffer_;
    std::vector<std::shared_ptr<Shader>> effects_;

    friend class Application;
};

#endif /* VIEWPORT_H */
