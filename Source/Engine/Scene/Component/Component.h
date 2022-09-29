#pragma once

#include <glm/glm.hpp>

namespace Kyst {

class Entity;
class Component {
 public:
  virtual ~Component() {}
  Entity* GetEntity() { return entity_; };

 protected:
  Entity* entity_;

 private:
  friend class Entity;
};

class Updatable : public Component {
 public:
  virtual void Update(float deltaTime) = 0;
};

class Drawable : public Component {
 public:
  virtual void Draw(const glm::mat4& uModel, const glm::mat4& uView, const glm::mat4& uProjection) = 0;
};

}  // namespace Kyst
