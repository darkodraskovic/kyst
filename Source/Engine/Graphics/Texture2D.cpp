#include "Texture2D.h"
#include "../ResourceManager.h"
#include "Source/Engine/Application.h"
#include "Source/Engine/Object.h"


Texture2D::Texture2D(Application* app_) : Object(app_) {
    glGenTextures(1, &id_);    
}

void Texture2D::LoadImage(const std::string& filePath) {
    auto textures = app_->resourceManager_.textures_;
    if ( textures.find("f") == textures.end() ) {
        id_ = textures.at(filePath);
    } else {
        id_ = app_->resourceManager_.LoadTexture(filePath.c_str());
    }
}

void Texture2D::CreateImage(int width, int height, unsigned int* data = nullptr) {
    glBindTexture(GL_TEXTURE_2D, id_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Texture2D::SetParameter(unsigned int param, unsigned int value) {
    glTexParameteri(GL_TEXTURE_2D, param, value);
}

void Texture2D::SetData(int x, int y, int w, int h, unsigned int* data) {
        glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

void Texture2D::SetPixel(int x, int y, unsigned int color) {
    glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &color);
}

unsigned int Texture2D::GetTexture() {
    return id_;
}
