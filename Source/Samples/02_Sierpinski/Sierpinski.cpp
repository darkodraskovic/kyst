#include "VecConsts.h"
#include "Sierpinski.h"

#include "SierpinskiFactory.h"

using namespace VecConsts;

Sierpinski::Sierpinski()
{
    material_ = std::shared_ptr<Material>(new Material);
    material_->shader_ = std::shared_ptr<Shader>(new Shader( "../Shaders/Magenta.vs", "../Shaders/Magenta.fs"));

    mesh_->GenArrayBuffer(SierpinskiFactory::Sierpinski2DDet(5));
}

void Sierpinski::Update(float deltaTime) {
    Rotate(deltaTime*45, FORWARD);
}
