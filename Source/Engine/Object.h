#ifndef OBJECT_H
#define OBJECT_H

class Application;
class Object
{
public:
    Object(Application* app): app_(app) {};

protected:
    Application* app_;
};


#endif /* OBJECT_H */
