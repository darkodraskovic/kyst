#include <map>
#include <string>

#include "Phong.h"

const std::map<PhongUniform, std::string> PHONG_MAP {
    {LIGHT_DIFFUSE, "uLight.diffuse"}, {LIGHT_SPECULAR, "uLight.specular"},
    {LIGHT_AMBIENT, "uLight.ambient"}, {LIGHT_POSITION, "uLight.position"},
    {MATERIAL_DIFFUSE, "uMaterial.diffuse"}, {MATERIAL_SPECULAR, "uMaterial.specular"},
    {MATERIAL_AMBIENT, "uMaterial.ambient"}, {MATERIAL_SHININESS, "uMaterial.shininess"},
    {MATERIAL_EMISSIVE, "uMaterial.emissive"}, {VIEW_POS, "uViewPos"},
};

Phong::Phong(std::shared_ptr<Shader> shader) : Material(shader)
{
}

void Phong::Update(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
{
    Material::Update(model, view, projection);

    shader_->SetVec3(PHONG_MAP.at(LIGHT_DIFFUSE),  lightDiffuse_);
    shader_->SetVec3(PHONG_MAP.at(LIGHT_SPECULAR), lightSpecular_);
    shader_->SetVec3(PHONG_MAP.at(LIGHT_AMBIENT),  lightAmbient_);
    shader_->SetVec3(PHONG_MAP.at(LIGHT_POSITION), lightPosition_);
    shader_->SetFloat(PHONG_MAP.at(MATERIAL_SHININESS), shininess_);
    shader_->SetVec3(PHONG_MAP.at(VIEW_POS), glm::vec3(glm::inverse(view)[3]));
}
