#include <iostream>
#include <utility>

#include "Core.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "ResourceManager.h"

namespace Kyst {

ResourceManager::ResourceManager(){};

bool ResourceManager::IsTextureLoaded(const std::string& filePath) { return textures_.find(filePath) != textures_.end(); }

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int ResourceManager::LoadTexture(const std::string& path) {
  if (IsTextureLoaded(path)) {
    return textures_.at(path);
  }

  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, numComponents;
  unsigned char* data = stbi_load(path.c_str(), &width, &height, &numComponents, 0);
  if (data) {
    GLenum format;
    if (numComponents == 1)
      format = GL_RED;
    else if (numComponents == 3)
      format = GL_RGB;
    else if (numComponents == 4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    textures_[path] = textureID;
  } else {
    std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
  }

  return textureID;
}

}  // namespace Kyst
