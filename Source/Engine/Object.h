#ifndef OBJECT_H
#define OBJECT_H

#include "Source/Engine/Application.h"
class Object
{
public:
    Object(Application* app): app_(app) {};

protected:
    Application* app_;
};


#endif /* OBJECT_H */
