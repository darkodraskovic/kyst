#include <iostream>
#include <cassert>
#include <glm/ext/scalar_constants.hpp>
#include <glm/fwd.hpp>

#include "Engine/Application.h"
#include "Engine/Scene/Entity.h"
#include "Engine/Graphics/Material2D.h"

#include "ShapeFactory/Shape2DFactory.h"
#include "Assert.h"

#include "Engine/VecConsts.h"
using namespace VecConsts;

using namespace ShapeFactory;

class App : public Application {
public:
    virtual int Init() {
        Application::Init();

        auto viewport = AddViewport(true);
        auto cam = viewport->scene_->camera_;
        cam->position_.z = 5;
        cam->LookAt(ZERO);

        auto material = new Material2D();
        material->color_ = GREEN;
        auto mesh = Shape2DFactory::SolidEllipse(ZERO, ONE*2.f);
        mesh->Generate(material->shader_->id_);
        auto entity = new Entity(mesh, material);
        viewport->scene_->AddEntity(entity);

        return 0;
    }

    virtual void ProcessInput() {
        Application::ProcessInput();
        if(input_->GetKey(GLFW_KEY_ESCAPE)) Close();
    }
    
    virtual void Update(float deltaTime) {
        viewports_[0]->scene_->camera_->ProcessInput(input_, deltaTime_);
        Application::Update(deltaTime);
    }
};

int main()
{
    assertColllide();
    
    App app;
    if (app.Init() < 0)
    {
        std::cout << "Failed to create an OpenGL app" << std::endl;
        return -1;
    };

    while (!app.ShouldClose())
    {
        app.Run();
    }
    
    app.Terminate();

    return 0;
}

