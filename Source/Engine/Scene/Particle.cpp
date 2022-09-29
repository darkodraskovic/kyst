#include "Particle.h"

namespace Kyst {

Particle::Particle() {}

void Particle::Update(float deltaTime) {
  Mover::Update(deltaTime);

  lifespan_ -= deltaTime;
  if (lifespan_ < 0) remove_ = true;
}

}  // namespace Kyst
