#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

class ResourceManager {
 public:
  ResourceManager();
  unsigned int LoadTexture(char const* path);

  std::map<std::string, unsigned int> textures_;
};

#endif
