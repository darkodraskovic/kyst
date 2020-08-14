#ifndef ENTITY_H
#define ENTITY_H

#include "Mesh.h"
#include "Material.h"
#include "Scene.h"

class Entity
{
public:
    Entity();
    Entity(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);
    
    virtual void Update(float deltaTime);
    virtual void Draw(const glm::mat4& uView, const glm::mat4& uProjection);
    Scene* GetScene();
    
    std::shared_ptr<Material> material_;
    std::shared_ptr<Mesh> mesh_;

    bool visible_ = true;

    vec3 position_ = vec3(0.f);
    vec3 rotation_ = vec3(0.f);
    vec3 scale_ = vec3(1.f);

    bool remove_ = false;

private:    
    Scene* scene_;
    friend class Scene;
};

#endif
