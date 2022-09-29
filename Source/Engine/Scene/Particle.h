
#include "Mover.h"

namespace Kyst {

class Particle : public Mover {
 public:
  Particle();
  void Update(float deltaTime) override;

  float lifespan_ = 1.f;  // secs
};

}  // namespace Kyst
