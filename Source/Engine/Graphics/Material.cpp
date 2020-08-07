#include "Material.h"
#include <GLFW/glfw3.h>

using namespace glm;

Material::Material()
{
};

Material::Material(std::shared_ptr<Shader> shader)
{
    shader_ =  shader;
};

Material::Material(const char* vertexPath, const char* fragmentPath)
{
    shader_ =  std::make_shared<Shader>(vertexPath, fragmentPath);
};

void Material::Update(float deltaTime, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
{
    shader_->Use();

    shader_->SetFloat("uTime", glfwGetTime());
    shader_->SetVec3("uColor", color_);
    shader_->SetFloat("uAlpha", alpha_);
    
    shader_->SetMat4("uModel", model);
    shader_->SetMat4("uView", view);
    shader_->SetMat4("uProjection", projection);
}
