#include "PhongCol.h"

PhongCol::PhongCol(std::shared_ptr<Shader> shader) : Phong(shader)
{
}

void PhongCol::Update(float deltaTime, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
{
    Phong::Update(deltaTime, model, view, projection);
    
    shader_->SetVec3("uMaterial.ambient",  ambient_);
    shader_->SetVec3("uMaterial.diffuse",  diffuse_);
    shader_->SetVec3("uMaterial.specular", specular_);
}
