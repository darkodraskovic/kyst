#ifndef FRAMBUFFER_H
#define FRAMBUFFER_H

#include "Mesh.h"
#include "Shader.h"

class Framebuffer
{
public:
    Framebuffer();
    Framebuffer(const std::string& fragmentPath, unsigned int width, unsigned int height);
    ~Framebuffer();
    
    void GenFramebuffer(unsigned int width, unsigned int height);
    void GenRenderbuffer(unsigned int width, unsigned int height);
    static std::shared_ptr<Shader> GenShader(const std::string& fragmentPath);
    
    void Bind();
    static void Unbind();

    void Draw();
    unsigned int Texture();
    
    unsigned int framebuffer_;
    unsigned int colorbuffer_;
    unsigned int renderbuffer_;
    std::shared_ptr<Shader> shader_;
    std::shared_ptr<Mesh> mesh_;


private:
    static const std::string vertexPath_;
    void GenMesh();
};

#endif /* FRAMBUFFER_H */
