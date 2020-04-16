#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"
#include "PhongMap.h"
#include "Shader.h"

#include "VecConsts.h"
#include "Cube.h"

using namespace VecConsts;

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
    auto material = std::shared_ptr<PhongMap>(new PhongMap(litTexShader));
    material->diffuse_ = diffuseMetal;
    material->emissive_ = emissiveMetal;
    material->specular_ = specularMetal;
    material->shininess_ = 1024.0f;
    auto cube2 = std::make_shared<Cube>(material);
    cube2->scale_ *= 2;
    app.entities_.push_back(cube2);

    material = std::shared_ptr<PhongMap>(new PhongMap(litTexShader));    
    material->diffuse_ = diffuseBricks;
    material->specular_ = specularBricks;
    material->emissive_ = emissiveBricks;
    material->shininess_ = 128.0f;
    auto cube4 = std::make_shared<Cube>(material);
    cube4->position_ = ONE*2.0f;
    cube4->scale_*= 2;
    app.entities_.push_back(cube4);

    litTexShader->Use();
    litTexShader->SetVec3("uLight.ambient",  DARK_GRAY);
    litTexShader->SetVec3("uLight.diffuse",  GRAY);
    litTexShader->SetVec3("uLight.specular", GRAY);
    litTexShader->SetVec3("uLight.position", 0.5f, 0.0f, 5.0f);

    app.camera_.position_.z = 12.0f;
    
    // Application loop
    // ---------------------------------------------------------------------------
    while (!app.ShouldClose())
    {

        float time = glfwGetTime();
        float sinVal = glm::sin(time);
        float cosVal = glm::cos(time);
        vec3 col = vec3(cosVal, 0.0f, sinVal);
        litTexShader->Use();
        litTexShader->SetVec3("uLight.position", col*5.0f);
        
        app.Update();
    }

    // Application termination
    // ---------------------------------------------------------------------------
    app.Terminate();
    return 0;
}
