#ifndef CUBE_H
#define CUBE_H

#include "Material.h"
#include "Entity.h"

class Cube : public Entity
{
public:
    Cube(const std::shared_ptr<Material>& material);
    virtual void Update(float time) override;
};

#endif
