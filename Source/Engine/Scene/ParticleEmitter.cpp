#include "ParticleEmitter.h"

#include <glm/gtc/random.hpp>
#include <string>

#include "Scene.h"

namespace Kyst {

ParticleEmitter::ParticleEmitter() { visible_ = false; }

void ParticleEmitter::CreateParticle() {
  auto particle = std::make_shared<Particle>();
  // particle->SetModel(GetModel());

  particle->position_ = position_;
  if (uniformScale_) {
    float scl = linearRand(minScale_.x, maxScale_.x);
    particle->scale_ = vec3(scl);
  } else {
    particle->scale_ = linearRand(minScale_, maxScale_);
  }

  particle->velocity_ = linearRand(minVelocity_, maxVelocity_);
  particle->acceleration_ = linearRand(minAcceleration_, maxAcceleration_);
  particle->mass_ = linearRand(minMass_, maxMass_);
  particle->gravity_ = linearRand(minGravity_, maxGravity_);
  particle->drag_ = linearRand(minDrag_, maxDrag_);

  particle->aVelocity_ = linearRand(minAVelocity, maxAVelocity);
  particle->aDrag_ = linearRand(minADrag_, maxADrag_);

  particle->lifespan_ = linearRand(minLifespan_, maxLifespan_);

  GetScene()->AddEntity(particle);
}

void ParticleEmitter::Update(float deltaTime) {
  Entity::Update(deltaTime);

  lastEmitted_ += deltaTime;
  if (lastEmitted_ > emissionFreq_) {
    CreateParticle();
    lastEmitted_ -= emissionFreq_;
  }
}

}  // namespace Kyst
