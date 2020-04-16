#include <glm/gtc/random.hpp>

#include "Application.h"
#include "Particle.h"
#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(Mesh* mesh, Material* material)
{
    mesh_ = std::shared_ptr<Mesh>(mesh);
    material_ = std::shared_ptr<Material>(material);
}

void ParticleEmitter::CreateParticle()
{
    auto particle = std::make_shared<Particle>();
    particle->material_ = material_;
    particle->mesh_ = mesh_;
    InitParticle(particle.get());
    Application::Instance().entities_.push_back(particle);
}

void ParticleEmitter::InitParticle(Particle* particle)
{
    particle->SetTranslation(position_);
    particle->SetScale(linearRand(minScale_, maxScale_));
    
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
    lastEmitted_ += deltaTime;
    if (lastEmitted_ > emissionFreq_) {
        CreateParticle();
        lastEmitted_ -= emissionFreq_;
    }
}
