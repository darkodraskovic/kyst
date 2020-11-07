#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "../Object.h"
#include "../Application.h"
#include <glad/glad.h>

#include <string>
class Texture2D : public Object
{
public:
    Texture2D(Application* app);
    void LoadImage(const std::string& filePath);
    void CreateImage(int width, int height, unsigned int* data);
    void SetData(int x, int y, int w, int h, unsigned int* data);
    void GetData(unsigned int* data);
    void SetParameter(unsigned int param, unsigned int value);
    unsigned int GetTexture();

private:
    unsigned int id_;
};


#endif /* TEXTURE2D_H */
