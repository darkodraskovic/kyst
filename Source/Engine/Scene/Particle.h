#ifndef PARTICLE_H
#define PARTICLE_H

#include "Mover.h"

class Particle : public Mover
{
public:
    Particle();
    void Update(float deltaTime) override;
    
    float lifespan_ = 1.f; // secs
};

#endif /* PARTICLE_H */
