#include "Mover.h"

#include "../../VecConsts.h"
#include "../Entity.h"

namespace Kyst {

using namespace VecConsts;

Mover::Mover() {}

void Mover::ApplyForce(const vec3& force) { acceleration_ += force / mass_; }

void Mover::Drag() {
  vec3 drag = glm::normalize(velocity_ * -1.f);
  float speed = glm::length(velocity_);
  if (!speed) return;  // TODO: when commented out, we get NaN
  drag *= drag_ * speed * speed;
  ApplyForce(drag);
}

void Mover::Update(float deltaTime) {
  // linear
  ApplyForce(gravity_);
  Drag();
  velocity_ += acceleration_ * deltaTime;

  if (glm::length(velocity_) < minSpeed_ && glm::length(acceleration_) < 1e-6) {
    velocity_ *= 0.f;
  } else {
    velocity_ = glm::clamp(velocity_, -maxVelocity_, maxVelocity_);
  }
  entity_->position_ += velocity_ * deltaTime;
  acceleration_ *= 0.f;

  // angular
  aVelocity_ *= ONE - aDrag_ * 1e-3f;
  aVelocity_ += aAcceleration_ * deltaTime;

  if (glm::length(aVelocity_) < minASpeed_ && glm::length(aAcceleration_) < 1e-6) {
    aVelocity_ *= 0.0f;
  } else {
    aVelocity_ = glm::clamp(aVelocity_, -maxAVelocity_, maxAVelocity_);
  }
  entity_->rotation_ += aVelocity_ * deltaTime;
  aAcceleration_ *= 0.f;
}

}  // namespace Kyst
