#include "Application.h"
#include "Material2D.h"
#include "Shape2DFactory.h"
#include "VecConsts.h"
#include "Viewport.h"
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

    // Viewport
    // ---------------------------------------------------------------------------
    
    auto viewport = std::make_shared<Viewport>();
    app.AddViewport(viewport);
    
    app.camera_ = viewport->GetScene()->camera_;
    app.camera_->position_.z = 3.0f;
    
    // viewport->AddEffect("../Shaders/Effects/Noop.fs");
    // viewport->AddEffect("../Shaders/Effects/Inversion.fs");
    // viewport->AddEffect("../Shaders/Effects/Remove.fs");
    
    // Application CONTENT
    // ---------------------------------------------------------------------------

    // material
    auto material = make_shared<Material2D>("../Shaders/GenArt/01.fs");

    // mesh
    auto mesh = Shape2DFactory::SolidRect(LEFT + DOWN, glm::vec2(2, 2));
    mesh->Generate();

    // entity
    auto entity = make_shared<Entity>(mesh, material);
    viewport->GetScene()->AddEntity(entity);

    // Reset POINTERS
    // ---------------------------------------------------------------------------
    
    material.reset();
    mesh.reset();
    entity.reset();
    viewport.reset();

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
