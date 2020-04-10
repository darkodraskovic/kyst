#ifndef SIERPINSKI_H
#define SIERPINSKI_H

#include "Material.h"
#include "Entity.h"

class Sierpinski : public Entity
{
public:
    Sierpinski();
    virtual void Update(float time) override;
};

#endif
