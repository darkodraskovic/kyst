#include "Texture2D.h"

#include "../Application.h"

Texture2D::Texture2D(Application* app) : Object(app) {}

void Texture2D::LoadImage(const std::string& filePath) {
  id_ = app_->resourceManager_.LoadTexture(filePath.c_str());
}

void Texture2D::CreateImage(int width, int height, unsigned int* data = nullptr,
                            GLuint interpolation) {
  glGenTextures(1, &id_);
  glBindTexture(GL_TEXTURE_2D, id_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, interpolation);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, interpolation);
}

void Texture2D::SetParameter(unsigned int param, GLuint value) {
  glBindTexture(GL_TEXTURE_2D, id_);
  glTexParameteri(GL_TEXTURE_2D, param, value);
}

// cf. https://www.khronos.org/opengl/wiki/Pixel_Transfer
void Texture2D::SetData(int x, int y, int w, int h, unsigned int* data) {
  glBindTexture(GL_TEXTURE_2D, id_);
  glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE,
                  data);
}

void Texture2D::GetData(unsigned int* data) {
  glBindTexture(GL_TEXTURE_2D, id_);
  glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

unsigned int Texture2D::GetId() { return id_; }
