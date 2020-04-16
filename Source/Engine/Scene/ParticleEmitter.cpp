#include <glm/gtc/random.hpp>

#include "Application.h"
#include "Particle.h"
#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter()
{
    visible_ = false;
}

void ParticleEmitter::CreateParticle()
{
    auto particle = std::make_shared<Particle>();
    particle->material_ = material_;
    particle->mesh_ = mesh_;
    InitParticle(particle.get());
    Application::Instance().CreateEntity(particle);
}

void ParticleEmitter::InitParticle(Particle* particle)
{
    particle->position_ = position_;
    particle->scale_ = linearRand(minScale_, maxScale_);
    
    particle->velocity_ = linearRand(minVelocity_, maxVelocity_);
    particle->acceleration_ = linearRand(minAcceleration_, maxAcceleration_);
    particle->mass_ = linearRand(minMass_, maxMass_);
    particle->gravity_ = linearRand(minGravity_, maxGravity_);
    particle->drag_ = linearRand(minDrag_, maxDrag_);

    particle->aVelocity_ = linearRand(minAVelocity, maxAVelocity);
    particle->aDrag_ = linearRand(minADrag_, maxADrag_);

    particle->lifespan_ = linearRand(minLifespan_, maxLifespan_);
}

void ParticleEmitter::Update(float deltaTime)
{
    Entity::Update(deltaTime);
    
    lastEmitted_ += deltaTime;
    if (lastEmitted_ > emissionFreq_) {
        CreateParticle();
        lastEmitted_ -= emissionFreq_;
    }
}
