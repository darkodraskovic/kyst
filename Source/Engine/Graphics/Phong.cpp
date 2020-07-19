#include "Phong.h"

Phong::Phong(std::shared_ptr<Shader> shader) : Material(shader)
{
}

void Phong::Update(float deltaTime, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
{
    Material::Update(deltaTime, model, view, projection);

    shader_->SetVec3("uLight.ambient",  lightAmbient_);
    shader_->SetVec3("uLight.diffuse",  lightDiffuse_);
    shader_->SetVec3("uLight.specular", lightSpecular_);
    shader_->SetVec3("uLight.position", lightPosition_);
    shader_->SetFloat("uMaterial.shininess", shininess_);
    shader_->SetVec3("uViewPos", glm::vec3(glm::inverse(view)[3]));
}
