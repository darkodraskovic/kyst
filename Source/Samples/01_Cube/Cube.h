#ifndef CUBE_H
#define CUBE_H

#include "Engine/Scene/Entity.h"
#include "ShapeFactory/CubeFactory.h"
#include <glm/gtc/constants.hpp>

using namespace ShapeFactory;

class Cube : public Entity
{
public:
    Cube(const std::shared_ptr<Material>& material) {
        material_ = material;
        mesh_ = CubeFactory::GetMesh();
        mesh_->Generate(material->shader_->id_);
    };
    
    virtual void Update(float deltaTime) override {
        // rotation_.y += deltaTime * glm::quarter_pi<float>();
    };
};

#endif
