#include "Material2D.h"

Material2D::Material2D()
{
    shader_ = std::make_shared<Shader>("../Shaders/2D.vs", "../Shaders/2D.fs");
}

Material2D::Material2D(std::shared_ptr<Shader> shader) : Material(shader)
{
}

void Material2D::Update(float deltaTime, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
{
    Material::Update(deltaTime, model, view, projection);

    // set sampler2d
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_);
    shader_->SetInt("uTexture", 0);

    // set float
    shader_->SetFloat("uPctCol", pctColor_);
    shader_->SetFloat("uPctTex", pctTexture_);
}
