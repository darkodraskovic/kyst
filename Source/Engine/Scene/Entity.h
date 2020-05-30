#ifndef ENTITY_H
#define ENTITY_H

#include "Mesh.h"
#include "Material.h"

class Entity
{
public:
    Entity();
    
    virtual void Update(float deltaTime);
    virtual void Draw(float deltaTime, const glm::mat4& uView, const glm::mat4& uProjection);

    std::shared_ptr<Material> material_;
    std::shared_ptr<Mesh> mesh_;

    bool visible_ = true;

    vec3 position_ = vec3(0.f);
    vec3 rotation_ = vec3(0.f);
    vec3 scale_ = vec3(1.f);

    bool remove_ = false;
};

#endif
