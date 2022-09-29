#pragma once

#include "../VecConsts.h"
#include "Phong.h"

using namespace glm;

namespace Kyst {

class PhongCol : public Phong {
 public:
  PhongCol();
  virtual void Update(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) override;

  vec3 ambient_{WHITE};
  vec3 diffuse_{WHITE};
  vec3 specular_{WHITE};
};

}  // namespace Kyst
