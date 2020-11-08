#include "Engine/Application.h"
#include "Engine/Graphics/PhongMap.h"
#include "Engine/Graphics/Framebuffer.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Scene/Viewport.h"
#include "Engine/VecConsts.h"
#include "Engine/Scene/PerspectiveCamera.h"

#include "Cube.h"

using namespace VecConsts;
using namespace glm;

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
    viewport->scene_->camera_->position_.z = 12.0f;
    viewport->AddEffect("Shaders/Effects/Noop.fs");
    // viewport->AddEffect("Shaders/Effects/Remove.fs");
    // viewport->AddEffect("Shaders/Effects/Inversion.fs");

    // Application CONTENT
    // ---------------------------------------------------------------------------

    unsigned int diffuseBricks = app.resourceManager_.LoadTexture("Assets/bricks_diffuse.jpg");
    unsigned int specularBricks = app.resourceManager_.LoadTexture("Assets/bricks_specular.jpg");
    unsigned int emissiveBricks = app.resourceManager_.LoadTexture("Assets/bricks_emissive_green.png");
    unsigned int diffuseMetal = app.resourceManager_.LoadTexture("Assets/metal_diffuse.jpg");
    unsigned int specularMetal = app.resourceManager_.LoadTexture("Assets/metal_specular.jpg");
    unsigned int emissiveMetal = app.resourceManager_.LoadTexture("Assets/metal_emissive_red.png");
    
    auto litTexShader = std::shared_ptr<Shader>(
        new Shader( "Shaders/LitTex.vs", "Shaders/LitTex.fs"));

    int size = 320;
    auto vp = Viewport::Create(&app, true, size, size);
    vp->AddEffect("Shaders/Textures/Tex2D.fs");
    vp->AddEffect("Shaders/Effects/Inversion.fs");
    vp->Render();
    glBindTexture(GL_TEXTURE_2D, vp->GetTexture()->GetId());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
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

    // Reset POINTERS
    // ---------------------------------------------------------------------------
    
    // vp.reset();
    material.reset();
    cube2.reset();
    cube4.reset();        

    viewport->scene_->camera_->LookAt(ZERO);
    // Application loop
    // ---------------------------------------------------------------------------
    while (!app.ShouldClose())
    {
        viewport->scene_->camera_->ProcessInput(app.GetInput(), app.GetDeltaTime());
        app.Update();
    }
    
    // Application termination
    // ---------------------------------------------------------------------------
    app.Terminate();

    return 0;
}

