#include "Material.h"

using namespace glm;

const std::map<Uniform, std::string> UNIFORM_MAP{
    {TIME, "uTime"}, {COLOR, "uColor"}, {ALPHA, "uAlpha"}, {MODEL, "uModel"}, {VIEW, "uView"}, {PROJECTION, "uProjection"},
};

Material::Material(){};

void Material::SetShader(std::shared_ptr<Shader> shader) { shader_ = std::shared_ptr<Shader>(shader); }
Shader* Material::GetShader() { return shader_.get(); }

void Material::Update(const mat4& model, const mat4& view, const mat4& projection) {
  shader_->Use();

  shader_->SetFloat(UNIFORM_MAP.at(TIME), (float)glfwGetTime());
  shader_->SetVec3(UNIFORM_MAP.at(COLOR), color_);
  shader_->SetFloat(UNIFORM_MAP.at(ALPHA), alpha_);

  shader_->SetMat4(UNIFORM_MAP.at(MODEL), model);
  shader_->SetMat4(UNIFORM_MAP.at(VIEW), view);
  shader_->SetMat4(UNIFORM_MAP.at(PROJECTION), projection);
}
