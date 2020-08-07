#include "Application.h"
#include "Shader.h"
#include "Material2D.h"
#include "Includer.h"
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
    string vCode = Includer::Include("../Shaders/2D.vs");
    string fCode = Includer::Include("../Shaders/GenArt/03.fs");
    auto shader = std::make_shared<Shader>(vCode, fCode);
    auto material = make_shared<Material2D>(shader);

    // mesh
    auto mesh = Shape2DFactory::SolidRect(LEFT + DOWN, glm::vec2(2, 2));
    mesh->Generate();

    // entity
    auto entity = make_shared<Entity>(mesh, material);
    app.AddEntity(entity);

    app.camera_.position_.z = 3.0f;
    // app.AddEffect("../Shaders/Effects/Remove.fs");
    // app.AddEffect("../Shaders/Effects/Inversion.fs");

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
