#ifndef MOVER_H
#define MOVER_H

#include <glm/glm.hpp>
#include "Entity.h"

using namespace glm;

class Mover : public Entity
{
public:
    Mover();

    virtual void Update(float deltaTime) override;
    void ApplyForce(const vec3& force);
    void Drag();

    // linear
    vec3 velocity_ = vec3(0,0,0);
    float minSpeed_ = 0.05f;
    vec3 maxVelocity_ = vec3(4,4,4);
    vec3 acceleration_ = vec3(0,0,0);
    float mass_ = 1.0f;
    vec3 gravity_ = vec3(0,0,0);
    float dragC_ = 0.0f;

    // angular
    vec3 aVelocity_ = vec3(0,0,0);
    vec3 maxAVelocity_ = vec3(glm::radians(720.0f), glm::radians(720.0f), glm::radians(720.0f));
    vec3 aAcceleration_ = vec3(0,0,0);
    float minASpeed_ = glm::radians(5.0f);
    vec3 aDrag_ = vec3(0,0,0);

    float forceScale_ = 1e-3;
};


#endif /* MOVER_H */
