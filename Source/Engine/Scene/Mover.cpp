#include <math.h>
#include "VecConsts.h"
#include "Mover.h"

using namespace VecConsts;

Mover::Mover()
{
}

void Mover::ApplyForce(const vec3& force)
{
    acceleration_ += (force  * forceScale_) / mass_;
}

void Mover::Drag()
{
    vec3 drag = glm::normalize(velocity_ * -1.0f);
    float speed = glm::length(velocity_);
    if (!speed) return; // TODO: when commented out, we get NaN
    drag *= dragC_ * speed * speed;
    ApplyForce(drag);
}

void Mover::Update(float deltaTime)
{
    // linear
    ApplyForce(gravity_);
    Drag();
    velocity_ += acceleration_;

    velocity_ = glm::clamp(velocity_, -maxVelocity_, maxVelocity_);
    if (glm::length(velocity_) < minSpeed_) velocity_ *= 0;
    
    Translate(velocity_ * deltaTime);
    
    acceleration_ *= 0;

    // angular
    aVelocity_ += aAcceleration_;
    aVelocity_ = glm::clamp(aVelocity_, -maxAVelocity_, maxAVelocity_);
    Rotate(aVelocity_.x * deltaTime, RIGHT);
    Rotate(aVelocity_.y * deltaTime, UP);
    Rotate(aVelocity_.z * deltaTime, FORWARD);
    aAcceleration_ *= 0;
}
