#ifndef PHONG_COL_H
#define PHONG_COL_H

#include "Phong.h"

using namespace glm;

class PhongCol : public Phong {
 public:
  PhongCol();
  virtual void Update(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) override;

  vec3 ambient_{1.0f, 1.0f, 1.0f};
  vec3 diffuse_{1.0f, 1.0f, 1.0f};
  vec3 specular_{1.0f, 1.0f, 1.0f};
};

#endif
