#ifndef FRAMBUFFER_H
#define FRAMBUFFER_H

class Framebuffer
{
public:
    Framebuffer(unsigned int width, unsigned int height);
    ~Framebuffer();
    
    void GenFramebuffer(unsigned int width, unsigned int height);
    void GenRenderbuffer(unsigned int width, unsigned int height);
    
    void Bind();
    static void Unbind();

private:
    unsigned int framebuffer_;
    unsigned int colorbuffer_;
    unsigned int renderbuffer_;

    friend class Viewport;
};

#endif /* FRAMBUFFER_H */
