#include "Material2D.h"

const std::string Material2D::sprite2DVSPath_ = "Shaders/Sprite2D.vs";
const std::string Material2D::sprite3DVSPath_ = "Shaders/Sprite3D.vs";
const std::string Material2D::fragmentPath_ = "Shaders/Sprite.fs";

Material2D::Material2D(bool sprite2D, const std::string& fragmentPath)
{
    if (sprite2D) shader_ = std::make_shared<Shader>(sprite2DVSPath_, fragmentPath);
    else shader_ = std::make_shared<Shader>(sprite3DVSPath_, fragmentPath);
}

void Material2D::Update(const mat4& model, const mat4& view, const mat4& projection)
{
    Material::Update(model, view, projection);

    // set sampler2d
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_);
    shader_->SetInt("uTexture", 0);

    // set float
    shader_->SetFloat("uPctCol", pctColor_);
    shader_->SetFloat("uPctTex", pctTexture_);
}
