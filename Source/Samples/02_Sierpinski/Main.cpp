#include "Engine/Application.h"
#include "Engine/VecConsts.h"
#include "Engine/Scene/Viewport.h"
#include "ShapeFactory/ShapeUtils.h"
#include "EntityFactory.h"

using namespace VecConsts;
using namespace ShapeFactory;

class App : public Application {
public:
    virtual int Init() {
        Application::Init();
        
        // glEnable(GL_LINE_SMOOTH);
        glLineWidth(2.0f);
    
        auto viewport = AddViewport(true);
        viewport->scene_->clearColor_ = vec4(ShapeUtils::Hex2rgb("99B898"), 1.0);
        // viewport->AddEffect("Shaders/Effects/Noop.fs");
        // viewport->AddEffect("Shaders/Effects/Inversion.fs");
        // viewport->AddEffect("Shaders/Effects/Remove.fs");

        viewport->scene_->camera_->position_.z = 7.0f;
        viewport->scene_->camera_->position_.y = 5.0f;
    
        auto eFactory = new EntityFactory(viewport->scene_.get());
    
        eFactory->color1_ = ShapeUtils::Hex2rgb("E84A5F");
        eFactory->color2_ = ShapeUtils::Hex2rgb("FF847C");
        eFactory->color3_ = ShapeUtils::Hex2rgb("FECEAB");
        float limit = 0.05;
        eFactory->CreateLineGasket(4, vec2(-limit, limit), true, true);
        // eFactory->CreateTriGasket(4, vec2(-limit, limit), true, true);
        eFactory->CreateSnowflakeEmitter();

        viewport->scene_->camera_->LookAt(ZERO);
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

    while (!app.ShouldClose()) app.Run();

    app.Terminate();

    return 0;
}
