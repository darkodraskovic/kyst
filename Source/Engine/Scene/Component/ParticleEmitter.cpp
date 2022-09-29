#include "ParticleEmitter.h"

#include <glm/gtc/random.hpp>
#include <string>

#include "../Entity.h"
#include "../Scene.h"
#include "ModelComponent.h"
#include "Mover.h"

namespace Kyst {

class Particle : public Entity {
 public:
  Particle() { AddComponent<Mover>(); };

  void Update(float deltaTime) override {
    Entity::Update(deltaTime);

    lifespan_ -= deltaTime;
    if (lifespan_ < 0) remove_ = true;
  };

  float lifespan_ = 1.f;  // secs
};

void ParticleEmitter::SetModel(std::shared_ptr<Model> model) { model_ = model; }

void ParticleEmitter::CreateParticle() {
  auto particle = std::make_shared<Particle>();
  particle->AddComponent<ModelComponent>()->SetModel(model_);
  entity_->GetScene()->AddEntity(particle);

  particle->position_ = entity_->position_;
  if (uniformScale_) {
    float scl = linearRand(minScale_.x, maxScale_.x);
    particle->scale_ = vec3(scl);
  } else {
    particle->scale_ = linearRand(minScale_, maxScale_);
  }

  auto* mover = particle->GetComponent<Mover>();
  mover->velocity_ = linearRand(minVelocity_, maxVelocity_);
  mover->acceleration_ = linearRand(minAcceleration_, maxAcceleration_);
  mover->mass_ = linearRand(minMass_, maxMass_);
  mover->gravity_ = linearRand(minGravity_, maxGravity_);
  mover->drag_ = linearRand(minDrag_, maxDrag_);

  mover->aVelocity_ = linearRand(minAVelocity, maxAVelocity);
  mover->aDrag_ = linearRand(minADrag_, maxADrag_);

  particle->lifespan_ = linearRand(minLifespan_, maxLifespan_);

  entity_->GetScene()->AddEntity(particle);
}

void ParticleEmitter::Update(float deltaTime) {
  lastEmitted_ += deltaTime;
  if (lastEmitted_ > emissionFreq_) {
    CreateParticle();
    lastEmitted_ -= emissionFreq_;
  }
}

}  // namespace Kyst
