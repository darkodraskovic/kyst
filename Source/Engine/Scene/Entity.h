#ifndef ENTITY_H
#define ENTITY_H

#include "../Graphics/Mesh.h"
#include "../Graphics/Material.h"
#include "Scene.h"
#include <string>

class Entity
{
public:
    Entity();
    Entity(Mesh* mesh, Material* material);
    Entity(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);
    
    virtual void Update(float deltaTime);
    virtual void Draw(const glm::mat4& uView, const glm::mat4& uProjection);
    Scene* GetScene();
    
    std::shared_ptr<Material> material_;
    std::shared_ptr<Mesh> mesh_;

    std::string name_;
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
