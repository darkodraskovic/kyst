#pragma once

#include <glm/glm.hpp>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Component/Component.h"

using namespace glm;

namespace Kyst {

class Scene;

class Entity {
 public:
  virtual void Update(float deltaTime);
  virtual void Draw(const glm::mat4& uView, const glm::mat4& uProjection);

  void SetScene(Scene* scene);
  Scene* GetScene();

  std::string name_;
  bool visible_ = true;

  vec3 position_ = vec3(0.f);
  vec3 rotation_ = vec3(0.f);
  vec3 scale_ = vec3(1.f);

  // TODO: make private
  bool remove_ = false;

  template <typename T>
  T* AddComponent() {
    std::shared_ptr<T> component = std::make_shared<T>();
    component->entity_ = this;
    components_.emplace_back(component);

    T* raw = component.get();
    typeMap_[&typeid(T)] = raw;
    if (dynamic_cast<Updatable*>(raw)) updatables_.emplace_back(dynamic_cast<Updatable*>(raw));
    if (dynamic_cast<Drawable*>(raw)) drawables_.emplace_back(dynamic_cast<Drawable*>(raw));

    return raw;
  }

  template <typename T>
  T* GetComponent() {
    return static_cast<T*>(typeMap_[&typeid(T)]);
  }

  template <typename T>
  bool HasComponent() const {
    return typeMap_.find(&typeid(T)) != typeMap_.end();
  };

 protected:
  std::vector<std::shared_ptr<Component>> components_;
  std::map<const std::type_info*, Component*> typeMap_;

  std::vector<Updatable*> updatables_;
  std::vector<Drawable*> drawables_;

  Scene* scene_;
};

}  // namespace Kyst
