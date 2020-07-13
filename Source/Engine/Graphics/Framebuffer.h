#ifndef FRAMBUFFER_H
#define FRAMBUFFER_H

#include "Mesh.h"
#include "Shader.h"
#include <memory>

class Framebuffer
{
public:
    Framebuffer();
    void GenFramebuffer(unsigned int width, unsigned int height);
    void GenRenderbuffer(unsigned int width, unsigned int height);
    unsigned int GenTexture(unsigned int width, unsigned int height, const char* fragmentPath);
    
    unsigned int framebuffer_;
    unsigned int colorbuffer_;
    unsigned int renderbuffer_;
    std::shared_ptr<Shader> shader_;
    
private:
    std::shared_ptr<Mesh> mesh_;
};

#endif /* FRAMBUFFER_H */
