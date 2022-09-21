#ifndef OBJECT_H
#define OBJECT_H

class Application;
class Object {
 public:
  Object(Application* app) : app_(app){};
  const Application* GetApplication() const { return app_; }

 protected:
  Application* app_;
};

#endif /* OBJECT_H */
