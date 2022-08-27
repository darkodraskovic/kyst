#ifndef PHONG_COL_H
#define PHONG_COL_H

#include "Phong.h"

using namespace glm;

class PhongCol : public Phong {
 public:
  PhongCol();
  virtual void Update(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) override;

  vec3 ambient_;
  vec3 diffuse_;
  vec3 specular_;
};

#endif
