#include "Phong.h"

Phong::Phong(std::shared_ptr<Shader> shader) : Material(shader)
{
}

void Phong::Update(float deltaTime, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
{
    Material::Update(deltaTime, model, view, projection);
    
    shader_->SetVec3("uMaterial.ambient",  ambient_);
    shader_->SetVec3("uMaterial.diffuse",  diffuse_);
    shader_->SetVec3("uMaterial.specular", specular_);
    shader_->SetFloat("uMaterial.shininess", shininess_);
}
