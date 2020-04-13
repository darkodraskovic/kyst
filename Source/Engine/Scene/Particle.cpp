#include "Particle.h"

Particle::Particle()
{
}

void Particle::Update(float deltaTime)
{
    Mover::Update(deltaTime);

    lifespan_ -= deltaTime;
    if (lifespan_ < 0) Remove();
}
