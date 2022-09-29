#pragma once

#include <memory>
#include <vector>

// #include "Camera.h"
#include "Component/CameraComponent.h"
#include "Viewport.h"

namespace Kyst {

class Entity;

class Scene {
 public:
  void Update(float deltaTime);
  void Draw(unsigned int width, unsigned int height);
  void AddEntity(std::shared_ptr<Entity> entity);
  const Viewport* GetViewport() const;

  vec4 clearColor_ = vec4(0.2f, 0.3f, 0.3f, 1.0f);
  CameraComponent* cameraComponent_;

 private:
  std::vector<std::shared_ptr<Entity>> entities_;
  std::vector<std::shared_ptr<Entity>> entitiesToCreate_;
  std::vector<std::shared_ptr<Entity>> alphaEntities_;

  Viewport* viewport_;
  friend class Viewport;
};

}  // namespace Kyst
