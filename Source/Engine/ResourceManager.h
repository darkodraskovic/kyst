#pragma once

#include <map>
#include <string>

namespace Kyst {

class ResourceManager {
 public:
  ResourceManager();
  unsigned int LoadTexture(const std::string& path);

 private:
  bool IsTextureLoaded(const std::string& filePath);
  std::map<std::string, unsigned int> textures_;
};

}  // namespace Kyst
