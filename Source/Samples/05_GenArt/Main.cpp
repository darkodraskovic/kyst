#include "Application.h"
#include "Shader.h"
#include "Material2D.h"
#include "Shape2DFactory.h"
#include "VecConsts.h"
#include <glm/fwd.hpp>

using namespace VecConsts;

int main()
{
    // Application init
    // ---------------------------------------------------------------------------    
    Application app = Application::Instance();
    if (app.Init() < 0)
    {
        std::cout << "Failed to create an OpenGL app" << std::endl;
        return -1;
    };

    // Application CONTENT
    // ---------------------------------------------------------------------------

    // shader & material
    auto shader = std::make_shared<Shader>("../Shaders/2D.vs", "../Shaders/GenArt/01.fs");
    auto material = make_shared<Material2D>(shader);

    // mesh
    auto mesh = Shape2DFactory::SolidRect(LEFT + DOWN, glm::vec2(2, 2));
    mesh->Generate();

    // entity
    auto entity = make_shared<Entity>(mesh, material);
    app.AddEntity(entity);

    app.camera_.position_.z = 3.0f;
    // app.AddEffect("../Shaders/Effects/Inversion.fs");
    // app.AddEffect("../Shaders/Effects/Remove.fs");

    material.reset();
    mesh.reset();
    entity.reset();
    // Application loop
    // ---------------------------------------------------------------------------
    while (!app.ShouldClose())
    {
        app.Update();
    }

    
    // Application termination
    // ---------------------------------------------------------------------------
    app.Terminate();

    return 0;
}
