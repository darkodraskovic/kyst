#include <memory>
#include "Engine/Application.h"
#include "Engine/Scene/Entity.h"
#include "Engine/Graphics/Material2D.h"
#include "Engine/VecConsts.h"
#include "Engine/Scene/Viewport.h"
#include "ShapeFactory/Shape2DFactory.h"

using namespace VecConsts;
using namespace ShapeFactory;

Entity* GenEntity(const string& fragmentPath, const vec3& position = ZERO)
{
    auto material = new Material2D(fragmentPath);
    auto mesh = Shape2DFactory::SolidRect(LEFT + DOWN, glm::vec2(2, 2));
    mesh->Generate(material->shader_->id_);
    auto entity = new Entity(mesh, material);
    entity->position_ = position;
    return entity;
}

class App : public Application {
public:
    virtual int Init() {
        Application::Init();

        auto viewport = AddViewport(true);
        auto cam =  viewport->scene_->camera_;
        cam->position_.z = 7.0f;
        cam->LookAt(ZERO);
    
        // viewport->AddEffect("Shaders/Effects/Noop.fs");
        // viewport->AddEffect("Shaders/Effects/Inversion.fs");
        // viewport->AddEffect("Shaders/Effects/Remove.fs");
    
        viewport->scene_->AddEntity(GenEntity("Shaders/GenArt/01.fs", LEFT + DOWN));
        viewport->scene_->AddEntity(GenEntity("Shaders/GenArt/02.fs", RIGHT + DOWN));
        viewport->scene_->AddEntity(GenEntity("Shaders/GenArt/03.fs", RIGHT + UP));
        viewport->scene_->AddEntity(GenEntity("Shaders/GenArt/04_tiling.fs", LEFT + UP));
        
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
