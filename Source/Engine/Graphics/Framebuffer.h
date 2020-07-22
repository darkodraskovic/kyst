#ifndef FRAMBUFFER_H
#define FRAMBUFFER_H

#include "Mesh.h"
#include "Shader.h"
#include <memory>

class Framebuffer
{
public:
    Framebuffer();
    ~Framebuffer();
    
    void GenFramebuffer(unsigned int width, unsigned int height);
    void GenRenderbuffer(unsigned int width, unsigned int height);
    void GenShader(const char* fragmentPath);
    void Bind();
    void Render();
    unsigned int RenderTexture();
    
    unsigned int framebuffer_;
    unsigned int colorbuffer_;
    unsigned int renderbuffer_;
    std::shared_ptr<Shader> shader_;
    std::shared_ptr<Mesh> mesh_;
    
    static void Unbind();
};

#endif /* FRAMBUFFER_H */
