#include <math.h>
#include "VecConsts.h"
#include "Mover.h"

using namespace VecConsts;

Mover::Mover()
{
}

void Mover::ApplyForce(float deltaTime,const vec3& force)
{
    acceleration_ += (force / mass_) * deltaTime;
}

void Mover::Drag(float deltaTime)
{
    vec3 drag = glm::normalize(velocity_ * -1.f);
    float speed = glm::length(velocity_);
    if (!speed) return; // TODO: when commented out, we get NaN
    drag *= dragC_ * speed * speed;
    ApplyForce(deltaTime, drag);
}

void Mover::Update(float deltaTime)
{
    Entity::Update(deltaTime);

    // linear
    ApplyForce(deltaTime, gravity_);
    Drag(deltaTime);
    velocity_ += acceleration_;
    
    velocity_ = glm::clamp(velocity_, -maxVelocity_, maxVelocity_);
    if (glm::length(velocity_) < minSpeed_ && glm::length(acceleration_) < 1e-6) {
        velocity_ *= 0.f;
    }
    Translate(velocity_ * deltaTime);
    acceleration_ *= 0.f;

    // angular
    aVelocity_ *= ONE - deltaTime * aDrag_;
    aVelocity_ += aAcceleration_ * deltaTime; // we don't use angular force
    
    if (glm::length(aVelocity_) < minASpeed_ && glm::length(aAcceleration_) < 1e-6) {
        aVelocity_ *= 0.0f;
    }
    aVelocity_ = glm::clamp(aVelocity_, -maxAVelocity_, maxAVelocity_);
    
    Rotate(aVelocity_.x * deltaTime, RIGHT);
    Rotate(aVelocity_.y * deltaTime, UP);
    Rotate(aVelocity_.z * deltaTime, FORWARD);
    aAcceleration_ *= 0.f;
}
