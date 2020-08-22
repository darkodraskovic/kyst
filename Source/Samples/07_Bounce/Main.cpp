#include <cassert>
#include <iostream>
#include "Application.h"
#include "Entity.h"
#include "Material2D.h"
#include "Shape2DFactory.h"
#include "VecConsts.h"
#include "Shape.h"

using namespace VecConsts;

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

    // Application CONTENT
    // ---------------------------------------------------------------------------

    auto viewport = app.AddViewport();
    auto cam = viewport->GetScene()->camera_;
    cam->position_.z = 5;
    cam->LookAt(ZERO);

    auto material = new Material2D();
    material->color_ = GREEN;
    auto mesh = Shape2DFactory::SolidEllipse(ZERO, ONE*2.f);
    mesh->Generate();
    auto entity = new Entity(mesh, material);
    viewport->GetScene()->AddEntity(entity);

    using namespace Shape;
    
    // Rectangle a{{1,1}, {4,4}};
    // Rectangle b{{2,2}, {5,5}};
    // Rectangle c{{6,4}, {4,2}};
    // assert(collide(a,b));
    // assert(collide(b,c));
    // assert(!collide(a,c));

    // Circle a = {{4, 4}, 2};
    // Circle b = {{7, 4}, 2};
    // Circle c = {{10, 4}, 2};
    // assert(collide(a, b));
    // assert(collide(b, c));
    // assert(!collide(a, c));
    
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
