#include "PhongCol.h"

PhongCol::PhongCol(std::shared_ptr<Shader> shader) : Phong(shader)
{
}

void PhongCol::Update(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
{
    Phong::Update(model, view, projection);
    
    shader_->SetVec3(PHONG_MAP.at(MATERIAL_DIFFUSE),  diffuse_);
    shader_->SetVec3(PHONG_MAP.at(MATERIAL_SPECULAR), specular_);
    shader_->SetVec3(PHONG_MAP.at(MATERIAL_AMBIENT),  ambient_);
}
