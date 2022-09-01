#ifndef APPLICATION_H
#define APPLICATION_H

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>

#include "Input.h"
#include "ResourceManager.h"

using namespace glm;

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

class Viewport;

class Application {
 public:
  Application();

  virtual void Init();
  virtual void ProcessInput();
  virtual void Update(float deltaTime);
  virtual void Render();

  void Run();
  bool ShouldClose();
  void Close();
  void Terminate();

  float GetDeltaTime();
  Input* GetInput();
  ResourceManager& GetResourceManager();

  void SetWindowSize(const uvec2& size);
  const uvec2& GetWindowSize();
  void SetWindowPosition(const ivec2& size);
  const ivec2& GetWindowPosition();

  Viewport* AddViewport(bool perspective = true, int width = 0, int height = 0);
  void AddViewport(std::shared_ptr<Viewport> viewport);

 protected:
  std::vector<std::shared_ptr<Viewport>> viewports_;
  std::shared_ptr<Input> input_;
  float deltaTime_ = 0.0f;

 private:
  static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

  GLFWwindow* window_;
  uvec2 windowSize_{1152, 720};
  ivec2 windowPosition_{0, 0};

  ResourceManager resourceManager_;

  float lastFrame_ = 0.0f;
};

#endif
