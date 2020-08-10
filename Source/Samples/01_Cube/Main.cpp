#include "Application.h"
#include "PhongMap.h"
#include "Framebuffer.h"
#include "VecConsts.h"

#include "Cube.h"

using namespace VecConsts;
using namespace glm;

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

    // Application CONTENT
    // ---------------------------------------------------------------------------
    
    unsigned int diffuseBricks = app.resourceManager_.LoadTexture("../Assets/bricks_diffuse.jpg");
    unsigned int specularBricks = app.resourceManager_.LoadTexture("../Assets/bricks_specular.jpg");
    unsigned int emissiveBricks = app.resourceManager_.LoadTexture("../Assets/bricks_emissive_green.png");
    unsigned int diffuseMetal = app.resourceManager_.LoadTexture("../Assets/metal_diffuse.jpg");
    unsigned int specularMetal = app.resourceManager_.LoadTexture("../Assets/metal_specular.jpg");
    unsigned int emissiveMetal = app.resourceManager_.LoadTexture("../Assets/metal_emissive_red.png");
    
    auto litTexShader = std::shared_ptr<Shader>(
        new Shader( "../Shaders/LitTex.vs", "../Shaders/LitTex.fs"));

    auto fb = std::make_shared<Framebuffer>("../Shaders/Textures/Tex2D.fs", 640, 640);
    unsigned int texture = fb->Texture();
    fb.reset();
    
    auto material = std::shared_ptr<PhongMap>(new PhongMap(litTexShader));
    material->diffuse_ = diffuseMetal;
    material->diffuse_ = texture;
    material->emissive_ = emissiveMetal;
    material->specular_ = specularMetal;
    material->shininess_ = 1024.0f;
    material->lightPosition_ = vec3(0.5f, 0.0f, 5.0f);
    auto cube2 = std::make_shared<Cube>(material);
    cube2->scale_ *= 2;
    app.AddEntity(cube2);
    cube2.reset();

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
    app.AddEntity(cube4);
    cube4.reset();
    
    app.camera_.position_.z = 12.0f;

    app.AddEffect("../Shaders/Effects/Noop.fs");
    // app.AddEffect("../Shaders/Effects/Remove.fs");
    // app.AddEffect("../Shaders/Effects/Inversion.fs");
    
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
