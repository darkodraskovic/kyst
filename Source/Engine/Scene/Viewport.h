#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "Mesh.h"
#include "Framebuffer.h"
#include "Scene.h"

class Viewport
{
public:
    Viewport(unsigned int width, unsigned int height);
    Viewport(std::shared_ptr<Scene> scene_, unsigned int width, unsigned int height);
    void Render();
    void Draw();
    void AddEffect(const char* fragmentPath);

    vec3 position_ = vec3(0.f);
    unsigned int texture_;
    
    static const std::string vertexPath_;
    static const std::string fragmentPath_;

private:
    void GenBuffers(float width, float height);
    void GenQuad(float width, float height);

    unsigned int width_;
    unsigned int height_;
    
    std::shared_ptr<Mesh> quad_;
    std::shared_ptr<Shader> shader_;

    std::shared_ptr<Framebuffer> frontbuffer_;
    std::shared_ptr<Framebuffer> backbuffer_;
    std::vector<std::shared_ptr<Shader>> effects_;

    std::shared_ptr<Scene> scene_;
};

#endif /* VIEWPORT_H */
