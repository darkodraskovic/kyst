#include "Texture2D.h"

#include "../Application.h"

Texture2D::Texture2D(Application* app) : Object(app) {}

void Texture2D::LoadImage(const std::string& filePath) {
  auto textures = app_->resourceManager_.textures_;
  if (textures.find(filePath) == textures.end()) {
    id_ = app_->resourceManager_.LoadTexture(filePath.c_str());
  } else {
    id_ = textures.at(filePath);
  }
}

void Texture2D::CreateImage(int width, int height,
                            unsigned int* data = nullptr) {
  glGenTextures(1, &id_);
  glBindTexture(GL_TEXTURE_2D, id_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Texture2D::SetParameter(unsigned int param, unsigned int value) {
  glBindTexture(GL_TEXTURE_2D, id_);
  glTexParameteri(GL_TEXTURE_2D, param, value);
}

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
