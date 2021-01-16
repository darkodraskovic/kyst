#include "Engine/Application.h"
#include "Engine/Graphics/PhongCol.h"
#include "Engine/Graphics/PhongMap.h"
#include "Engine/Graphics/Framebuffer.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Scene/Viewport.h"
#include "Engine/VecConsts.h"
#include "Engine/Scene/PerspectiveCamera.h"

#include "Cube.h"

using namespace VecConsts;
using namespace glm;

class App : public Application {
public:
    virtual int Init() {
        Application::Init();
        auto viewport = AddViewport();    
        viewport->scene_->camera_->position_.z = 12.0f;
        viewport->AddEffect("Shaders/Effects/Noop.fs");
        // viewport->AddEffect("Shaders/Effects/Remove.fs");
        // viewport->AddEffect("Shaders/Effects/Inversion.fs");

        unsigned int diffuseBricks = resourceManager_.LoadTexture("Assets/bricks_diffuse.jpg");
        unsigned int specularBricks = resourceManager_.LoadTexture("Assets/bricks_specular.jpg");
        unsigned int emissiveBricks = resourceManager_.LoadTexture("Assets/bricks_emissive_green.png");
        unsigned int diffuseMetal = resourceManager_.LoadTexture("Assets/metal_diffuse.jpg");
        unsigned int specularMetal = resourceManager_.LoadTexture("Assets/metal_specular.jpg");
        unsigned int emissiveMetal = resourceManager_.LoadTexture("Assets/metal_emissive_red.png");
    
        auto litTexShader = std::shared_ptr<Shader>(
            new Shader( "Shaders/LitTex.vs", "Shaders/LitTex.fs"));
        auto litColShader = std::shared_ptr<Shader>(
            new Shader( "Shaders/LitCol.vs", "Shaders/LitCol.fs"));

        int size = 320;
        auto vp = Viewport::Create(this, true, size, size);
        vp->AddEffect("Shaders/Textures/Tex2D.fs");
        vp->AddEffect("Shaders/Effects/Inversion.fs");
        vp->Render();
    
        auto material = std::shared_ptr<PhongMap>(new PhongMap(litTexShader));
        material->diffuse_ = diffuseMetal;
        material->diffuse_ = vp->GetTexture()->GetId();
        material->emissive_ = emissiveMetal;
        material->specular_ = specularMetal;
        material->shininess_ = 1024.0f;
        material->lightPosition_ = vec3(0.5f, 0.0f, 5.0f);
        auto cube2 = std::make_shared<Cube>(material);
        cube2->scale_ *= 2;
        viewport->scene_->AddEntity(cube2);

        material = std::shared_ptr<PhongMap>(new PhongMap(litTexShader));    
        material->diffuse_ = diffuseBricks;
        material->emissive_ = emissiveBricks;
        material->specular_ = specularBricks;
        material->shininess_ = 128.0f;
        material->lightPosition_ = vec3(0.5f, 0.0f, 5.0f);
        auto cube4 = std::make_shared<Cube>(material);
        cube4->position_ = ONE*2.0f;
        cube4->scale_*= 2;
        cube4->material_->alpha_ = 0.5;
        viewport->scene_->AddEntity(cube4);

        auto material2 = std::shared_ptr<PhongCol>(new PhongCol(litColShader));
        material2->diffuse_ = BLUE;
        material2->specular_ = RED;
        material2->shininess_ = 128.0f;
        material2->lightPosition_ = vec3(0.5f, 0.0f, 5.0f);
        auto cube5 = std::make_shared<Cube>(material2);
        cube5->position_ = -ONE*2.0f;
        cube5->scale_*= 2;
        // cube5->material_->alpha_ = 0.5;
        viewport->scene_->AddEntity(cube5);

        // vp.reset();
        material.reset();
        cube2.reset();
        cube4.reset();        
        cube5.reset();        

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
    if (app.Init() < 0) {
        std::cout << "Failed to create an OpenGL app" << std::endl;
        return -1;
    };


    while (!app.ShouldClose()) {
        app.Run();
    }
    
    app.Terminate();

    return 0;
}
