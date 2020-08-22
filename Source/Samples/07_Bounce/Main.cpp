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
    
    Rectangle aR{{1,1}, {4,4}};
    Rectangle bR{{2,2}, {5,5}};
    Rectangle cR{{6,4}, {4,2}};
    assert(collide(aR,bR));
    assert(collide(bR,cR));
    assert(!collide(aR,cR));

    Circle aC{{4, 4}, 2};
    Circle bC{{7, 4}, 2};
    Circle cC{{10, 4}, 2};
    assert(collide(aC, bC));
    assert(collide(bC, cC));
    assert(!collide(aC, cC));
    
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
