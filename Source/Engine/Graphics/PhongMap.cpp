#include "PhongMap.h"

PhongMap::PhongMap() {}

void PhongMap::Update(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) {
  Phong::Update(model, view, projection);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, diffuse_);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, specular_);
  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, emissive_);

  shader_->SetInt(PHONG_MAP.at(MATERIAL_DIFFUSE), 0);
  shader_->SetInt(PHONG_MAP.at(MATERIAL_SPECULAR), 1);
  shader_->SetInt(PHONG_MAP.at(MATERIAL_EMISSIVE), 2);
}
