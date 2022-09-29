#pragma once

#include "Phong.h"

namespace Kyst {

class PhongMap : public Phong {
 public:
  PhongMap();

  virtual void Update(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) override;

  unsigned int diffuse_{0};
  unsigned int specular_{0};
  unsigned int emissive_{0};
};

}  // namespace Kyst
