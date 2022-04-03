#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <string>

#include "../Object.h"

class Texture2D : public Object {
 public:
  Texture2D(Application* app);
  void LoadImage(const std::string& filePath);
  void CreateImage(int width, int height, unsigned int* data);
  void SetData(int x, int y, int w, int h, unsigned int* data);
  void GetData(unsigned int* data);
  void SetParameter(unsigned int param, unsigned int value);
  unsigned int GetId();

 private:
  unsigned int id_;
};

#endif /* TEXTURE2D_H */
