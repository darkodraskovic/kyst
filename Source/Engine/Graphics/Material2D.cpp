#include "Material2D.h"

namespace Kyst {
const std::string Material2D::vertexPath_ = "Shaders/Sprite.vs";
const std::string Material2D::fragmentPath_ = "Shaders/Sprite.fs";

Material2D::Material2D(const std::string& fragmentPath) { shader_ = std::make_shared<Shader>(vertexPath_, fragmentPath); }

void Material2D::Update(const mat4& model, const mat4& view, const mat4& projection) {
  Material::Update(model, view, projection);

  // set sampler2d
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture_);
  shader_->SetInt("uTexture", 0);

  // set float
  shader_->SetFloat("uPctCol", pctColor_);
  shader_->SetFloat("uPctTex", pctTexture_);
}
}  // namespace Kyst
