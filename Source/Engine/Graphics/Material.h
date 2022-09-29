#pragma once

#include <glm/glm.hpp>
#include <map>
#include <memory>

#include "../Core.h"
#include "Shader.h"

using namespace glm;

namespace Kyst {

enum Uniform { TIME, COLOR, ALPHA, MODEL, VIEW, PROJECTION };
extern const std::map<Uniform, std::string> UNIFORM_MAP;

class Material {
 public:
  Material();

  virtual void Update(const mat4& model, const mat4& view, const mat4& projection);

  void SetShader(std::shared_ptr<Shader> shader);
  Shader* GetShader();

  vec3 color_ = vec3(1.0);
  float alpha_ = 1.0;

 protected:
  std::shared_ptr<Shader> shader_;
};

}  // namespace Kyst
