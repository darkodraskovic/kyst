#pragma once

#include "../Camera.h"
#include "Component.h"

class CameraComponent : public Updatable {
  virtual void Update(float deltaTime) override{};
};
