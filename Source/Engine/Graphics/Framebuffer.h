#ifndef FRAMBUFFER_H
#define FRAMBUFFER_H

#include "Mesh.h"
#include "Shader.h"
#include <memory>
#include <string>

class Framebuffer
{
public:
    Framebuffer();
    Framebuffer(const std::string& fragmentPath);
    ~Framebuffer();
    
    void GenFramebuffer(unsigned int width, unsigned int height);
    void GenRenderbuffer(unsigned int width, unsigned int height);
    
    void Bind();
    static void Unbind();
    
    void RenderScene();
    unsigned int RenderTexture();
    
    unsigned int framebuffer_;
    unsigned int colorbuffer_;
    unsigned int renderbuffer_;
    std::shared_ptr<Shader> shader_;
    std::shared_ptr<Mesh> mesh_;

    static const std::string vertexPath_;

private:
    void GenMesh();
};

#endif /* FRAMBUFFER_H */
