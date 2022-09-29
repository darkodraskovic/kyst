#pragma once

namespace Kyst {

class Application;
class Object {
 public:
  Object(Application* app) : app_(app){};
  const Application* GetApplication() const { return app_; }

 protected:
  Application* app_;
};

}  // namespace Kyst
