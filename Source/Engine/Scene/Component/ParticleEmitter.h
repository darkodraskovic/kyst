#pragma once

#include <glm/glm.hpp>

#include "../../Graphics/Model.h"
#include "../../VecConsts.h"
#include "Component.h"

using namespace glm;

namespace Kyst {

using namespace VecConsts;

class ParticleEmitter : public Updatable {
 public:
  void Update(float deltaTime) override;
  void SetModel(std::shared_ptr<Model> model);

  float emissionFreq_ = 1.f;

  float minLifespan_ = 0.5f;
  float maxLifespan_ = 1.5f;

  vec3 minScale_ = ONE / 2.f, maxScale_ = ONE * 2.f;
  bool uniformScale_ = true;

  vec3 minVelocity_ = LEFT / 2.f, maxVelocity_ = RIGHT / 2.f;
  vec3 minAcceleration_ = ZERO, maxAcceleration_ = ZERO;
  float minMass_ = .5f, maxMass_ = 1.5f;
  vec3 minGravity_ = DOWN / 2.f, maxGravity_ = DOWN;
  float minDrag_ = 0, maxDrag_ = 0;

  vec3 minAVelocity = ZERO, maxAVelocity = ZERO;
  float minADrag_ = 0, maxADrag_ = 0;

 private:
  void CreateParticle();

  std::shared_ptr<Model> model_;
  float lastEmitted_ = 0;
};

}  // namespace Kyst
