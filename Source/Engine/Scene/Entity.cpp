#include "Entity.h"
#include "VecConsts.h"

using namespace VecConsts;

#include <glm/gtc/matrix_transform.hpp>

Entity::Entity()
{
}

void Entity::Update(float deltaTime)
{
}

void Entity::Draw(float deltaTime, const glm::mat4& uView, const glm::mat4& uProjection)
{
    auto transform = glm::mat4(1.f);
    transform = glm::translate(transform, position_);
    transform = glm::rotate(transform, rotation_.x, RIGHT);
    transform = glm::rotate(transform, rotation_.y, UP);
    transform = glm::rotate(transform, rotation_.z, FORWARD);
    transform = glm::scale(transform, scale_);
    material_->Update(deltaTime, transform, uView, uProjection);
    mesh_->Render();
}
