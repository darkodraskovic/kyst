#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H

#include <glm/glm.hpp>

#include "Mesh.h"
#include "Material.h"
#include "Particle.h"
#include "VecConsts.h"

using namespace glm;
using namespace VecConsts;

class ParticleEmitter
{
public:
    ParticleEmitter(Mesh* mesh, Material* material);
    void CreateParticle();
    void Update(float deltaTime);

    vec3 position_ = ZERO;
    float emissionFreq_ = 1.f;

    float minLifespan_ = 0.5f; float maxLifespan_ = 1.5f;
    float minScale_ = 0.5f,  maxScale_ = 1.5f;
    
    vec3 minVelocity_ = LEFT/ 2.f, maxVelocity_ = RIGHT / 2.f;
    vec3 minAcceleration_ = ZERO, maxAcceleration_ = ZERO;
    float minMass_ = .5f, maxMass_ = 1.5f;
    vec3 minGravity_ = DOWN / 2.f, maxGravity_ = DOWN;
    float minDrag_ = 0, maxDrag_ = 0;

    vec3 minAVelocity = ZERO, maxAVelocity = ZERO;
    float minADrag_ = 0, maxADrag_ = 0;

private:
    void InitParticle(Particle* particle);
    
    std::shared_ptr<Mesh> mesh_;
    std::shared_ptr<Material> material_;
    float lastEmitted_ = 0;
};


#endif /* PARTICLE_EMITTER_H */