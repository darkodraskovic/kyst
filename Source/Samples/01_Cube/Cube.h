#ifndef CUBE_H
#define CUBE_H

#include "Entity.h"
#include "CubeFactory.h"
#include <glm/gtc/constants.hpp>

class Cube : public Entity
{
public:
    Cube(const std::shared_ptr<Material>& material) {
        material_ = material;
        mesh_ = CubeFactory::GetMesh();
    };
    
    virtual void Update(float deltaTime) override {
        rotation_.y += deltaTime * glm::quarter_pi<float>();
    };
};

#endif
