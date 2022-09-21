#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <memory>
#include <vector>

#include "../Graphics/Framebuffer.h"
#include "../Graphics/Shader.h"
#include "Object.h"

class Scene;
class Mesh;
class Viewport : public Object {
 public:
  Viewport(Application* app);
  void Init(unsigned int width, unsigned int height);
  void Update(float deltaTime);

  void Render();
  void DrawToBuffer();
  void AddEffect(const char* fragmentPath);

  Texture2D* GetTexture();
  Scene* GetScene();

  static std::shared_ptr<Viewport> Create(Application* app, bool perspective, int width, int height);

  vec3 position_ = vec3(0.f);
  vec3 scale_ = vec3(1.f);

 private:
  void GenBuffers(float width, float height);
  void GenQuad(float width, float height);
  void DrawToScreen();

  std::shared_ptr<Scene> scene_;

  unsigned int width_;
  unsigned int height_;

  std::shared_ptr<Mesh> quad_;
  std::shared_ptr<Shader> shader_;

  std::shared_ptr<Framebuffer> frontbuffer_;
  std::shared_ptr<Framebuffer> backbuffer_;
  Framebuffer* bound_;
  std::vector<std::shared_ptr<Shader>> effects_;
};

#endif /* VIEWPORT_H */
