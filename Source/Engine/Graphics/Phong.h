#ifndef PHONG_H
#define PHONG_H

#include "../VecConsts.h"
#include "Material.h"

using namespace glm;
using namespace VecConsts;

enum PhongUniform {
  LIGHT_DIFFUSE,
  LIGHT_SPECULAR,
  LIGHT_AMBIENT,
  LIGHT_POSITION,
  MATERIAL_DIFFUSE,
  MATERIAL_SPECULAR,
  MATERIAL_AMBIENT,
  MATERIAL_SHININESS,
  MATERIAL_EMISSIVE,
  VIEW_POS,
};
extern const std::map<PhongUniform, std::string> PHONG_MAP;

class Phong : public Material {
 public:
  Phong();
  virtual void Update(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) override;

  vec3 lightAmbient_ = GRAY;
  vec3 lightDiffuse_ = GRAY;
  vec3 lightSpecular_ = GRAY;
  vec3 lightPosition_ = ZERO;

  float shininess_;
};

#endif
