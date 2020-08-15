#include "Application.h"
#include "Entity.h"
#include "Material2D.h"
#include "Shape2DFactory.h"
#include "VecConsts.h"
#include "Viewport.h"
#include <memory>

using namespace VecConsts;

shared_ptr<Entity> GenEntity(const string& shader, const vec3& position)
{
    auto material = make_shared<Material2D>(shader);
    auto mesh = Shape2DFactory::SolidRect(LEFT + DOWN, glm::vec2(2, 2));
    mesh->Generate();
    auto entity = make_shared<Entity>(mesh, material);
    entity->position_ = position;
    return entity;
}

int main()
{
    // Application init
    // ---------------------------------------------------------------------------    
    Application app;
    if (app.Init() < 0)
    {
        std::cout << "Failed to create an OpenGL app" << std::endl;
        return -1;
    };

    // Viewport
    // ---------------------------------------------------------------------------
    
    auto viewport = std::make_shared<Viewport>(app.GetWindowSize());
    app.AddViewport(viewport);
    
    auto cam =  viewport->GetScene()->camera_;
    cam->position_.z = 6.0f;
    
    // viewport->AddEffect("../Shaders/Effects/Noop.fs");
    // viewport->AddEffect("../Shaders/Effects/Inversion.fs");
    // viewport->AddEffect("../Shaders/Effects/Remove.fs");
    
    // Application CONTENT
    // ---------------------------------------------------------------------------

    viewport->GetScene()->AddEntity(GenEntity("../Shaders/GenArt/01.fs", LEFT + DOWN));
    viewport->GetScene()->AddEntity(GenEntity("../Shaders/GenArt/02.fs", RIGHT + DOWN));
    viewport->GetScene()->AddEntity(GenEntity("../Shaders/GenArt/03.fs", RIGHT + UP));

    // Reset POINTERS
    // ---------------------------------------------------------------------------
    
    viewport.reset();

    cam->LookAt(ZERO);
    // Application loop
    // ---------------------------------------------------------------------------
    while (!app.ShouldClose())
    {
        cam->ProcessInput(app.GetInput(), app.GetDeltaTime());
        app.Update();
    }

    // Application termination
    // ---------------------------------------------------------------------------
    app.Terminate();

    return 0;
}
