#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H

#include <glm/glm.hpp>

#include "Entity.h"
#include "Particle.h"
#include "VecConsts.h"

using namespace glm;
using namespace VecConsts;

class ParticleEmitter : public Entity
{
public:
    ParticleEmitter();
    void Update(float deltaTime) override;
    
    void CreateParticle();

    float emissionFreq_ = 1.f;

    float minLifespan_ = 0.5f; float maxLifespan_ = 1.5f;
    vec3 minScale_ = ONE / 2.f,  maxScale_ = ONE * 2.f;
    
    vec3 minVelocity_ = LEFT/ 2.f, maxVelocity_ = RIGHT / 2.f;
    vec3 minAcceleration_ = ZERO, maxAcceleration_ = ZERO;
    float minMass_ = .5f, maxMass_ = 1.5f;
    vec3 minGravity_ = DOWN / 2.f, maxGravity_ = DOWN;
    float minDrag_ = 0, maxDrag_ = 0;

    vec3 minAVelocity = ZERO, maxAVelocity = ZERO;
    float minADrag_ = 0, maxADrag_ = 0;

private:
    void InitParticle(Particle* particle);
    
    float lastEmitted_ = 0;
};


#endif /* PARTICLE_EMITTER_H */
