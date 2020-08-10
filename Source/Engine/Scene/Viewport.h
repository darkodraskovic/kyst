#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "Mesh.h"
#include "Framebuffer.h"

class Viewport
{
public:
    Viewport(unsigned int width, unsigned int height);
    void Bind();
    void Render();
    void Draw();
    void AddEffect(const char* fragmentPath);

    vec3 position_ = vec3(0.f);
    unsigned int texture_;
    
    static const std::string vertexPath_;
    static const std::string fragmentPath_;

private:
    void GenQuad(float width, float height);
    
    std::shared_ptr<Mesh> quad_;
    std::shared_ptr<Shader> shader_;

    std::shared_ptr<Framebuffer> frontbuffer_;
    std::shared_ptr<Framebuffer> backbuffer_;
    std::vector<std::shared_ptr<Shader>> effects_;

};

#endif /* VIEWPORT_H */
