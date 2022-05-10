#include "Entity.h"
#include "../VecConsts.h"

using namespace VecConsts;

Entity::Entity() {}

Entity::Entity(Mesh* mesh, Material* material)
{
    mesh_ = std::shared_ptr<Mesh>(mesh);
    material_ = std::shared_ptr<Material>(material);
}

Entity::Entity(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
{
    mesh_ = mesh;
    material_ = material;
}

Scene* Entity::GetScene() { return scene_; }

void Entity::Update(float deltaTime) {}

void Entity::Draw(const glm::mat4& uView, const glm::mat4& uProjection)
{
    glm::mat4 transform = glm::translate(glm::mat4(1.f), position_);
    transform = glm::rotate(transform, rotation_.x, RIGHT);
    transform = glm::rotate(transform, rotation_.y, UP);
    transform = glm::rotate(transform, rotation_.z, FORWARD);
    transform = glm::scale(transform, scale_);
    material_->Update(transform, uView, uProjection);
    mesh_->Draw();
}
