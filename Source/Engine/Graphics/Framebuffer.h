#ifndef FRAMBUFFER_H
#define FRAMBUFFER_H

#include "../Application.h"
#include "Texture2D.h"
#include "../Object.h"

class Framebuffer : public Object
{
public:
    Framebuffer(Application* app);
    ~Framebuffer();

    void Init(unsigned int width, unsigned int height);

    void Bind();
    static void Unbind();

private:
    Texture2D* texture_;
    unsigned int framebuffer_;
      unsigned int renderbuffer_;

    friend class Viewport;
};

#endif /* FRAMBUFFER_H */
