#ifndef PHONG_MAP_H
#define PHONG_MAP_H

#include "Phong.h"

class PhongMap : public Phong {
 public:
  PhongMap();

  virtual void Update(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) override;

  unsigned int diffuse_{0};
  unsigned int specular_{0};
  unsigned int emissive_{0};
};

#endif
