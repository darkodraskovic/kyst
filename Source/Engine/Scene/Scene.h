#ifndef SCENE_H
#define SCENE_H

#include "../Object.h"
#include "Camera.h"
#include "Viewport.h"

class Entity;

class Scene : public Object {
 public:
  Scene(Application* app) : Object(app){};
  void Update(float deltaTime);
  void Draw(unsigned int width, unsigned int height);
  // void AddEntity(Entity* entity);
  void AddEntity(std::shared_ptr<Entity> entity);

  vec4 clearColor_ = vec4(0.2f, 0.3f, 0.3f, 1.0f);
  std::shared_ptr<Camera> camera_;

 private:
  std::vector<std::shared_ptr<Entity>> entities_;
  std::vector<std::shared_ptr<Entity>> entitiesToCreate_;
  std::vector<std::shared_ptr<Entity>> alphaEntities_;

  friend class Viewport;
};

#endif /* SCENE_H */
