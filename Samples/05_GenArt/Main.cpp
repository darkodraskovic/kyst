#include <memory>
#include "Engine/Application.h"
#include "Engine/Scene/Entity.h"
#include "Engine/Graphics/Material2D.h"
#include "Engine/VecConsts.h"
#include "Engine/Scene/Viewport.h"
#include "ShapeFactory/Shape2DFactory.h"

using namespace VecConsts;
using namespace ShapeFactory;

Entity* GenEntity(const string& fragmentPath, const vec3& position)
{
    auto material = new Material2D(fragmentPath);
    auto mesh = Shape2DFactory::SolidRect(LEFT + DOWN, glm::vec2(2, 2));
    mesh->Generate(material->shader_->id_);
    auto entity = new Entity(mesh, material);
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
    
    auto viewport = app.AddViewport();
    auto cam =  viewport->GetScene()->camera_;
    cam->position_.z = 6.0f;
    cam->LookAt(ZERO);
    
    // viewport->AddEffect("../Shaders/Effects/Noop.fs");
    // viewport->AddEffect("../Shaders/Effects/Inversion.fs");
    // viewport->AddEffect("../Shaders/Effects/Remove.fs");
    
    // Application CONTENT
    // ---------------------------------------------------------------------------

    viewport->GetScene()->AddEntity(GenEntity("../Shaders/GenArt/01.fs", LEFT + DOWN));
    viewport->GetScene()->AddEntity(GenEntity("../Shaders/GenArt/02.fs", RIGHT + DOWN));
    viewport->GetScene()->AddEntity(GenEntity("../Shaders/GenArt/03.fs", RIGHT + UP));

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
