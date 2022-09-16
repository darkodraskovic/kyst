#pragma once

#include <glm/glm.hpp>

class Entity;
class Component {
 public:
  virtual ~Component() {}
  Entity* GetEntity() { return entity_; };

 private:
  Entity* entity_;

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
