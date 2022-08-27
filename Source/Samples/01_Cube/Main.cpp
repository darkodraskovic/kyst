#include "Cube.h"
#include "Engine/Application.h"
#include "Engine/Graphics/Framebuffer.h"
#include "Engine/Graphics/PhongCol.h"
#include "Engine/Graphics/PhongMap.h"
#include "Engine/Scene/PerspectiveCamera.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Scene/Viewport.h"
#include "Engine/VecConsts.h"

using namespace VecConsts;
using namespace glm;

class App : public Application {
 public:
  virtual void Init() {
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

    auto litTexShader = std::make_shared<Shader>("Shaders/LitTex.vs", "Shaders/LitTex.fs");
    auto litColShader = std::make_shared<Shader>("Shaders/LitCol.vs", "Shaders/LitCol.fs");

    int size = 320;
    auto vp = Viewport::Create(this, true, size, size);
    vp->AddEffect("Shaders/Textures/Tex2D.fs");
    vp->AddEffect("Shaders/Effects/Inversion.fs");
    vp->DrawToBuffer();

    auto material = std::make_shared<PhongMap>(litTexShader);
    // material->diffuse_ = diffuseMetal;
    material->diffuse_ = vp->GetTexture()->GetId();
    material->emissive_ = emissiveMetal;
    material->specular_ = specularMetal;
    material->shininess_ = 1024.0f;
    material->lightPosition_ = vec3(0.5f, 0.0f, 5.0f);
    auto cube1 = std::make_shared<Cube>(material);
    cube1->scale_ *= 2;
    viewport->scene_->AddEntity(cube1);

    auto material2 = std::make_shared<PhongMap>(litTexShader);
    material2->diffuse_ = diffuseBricks;
    material2->emissive_ = emissiveBricks;
    material2->specular_ = specularBricks;
    material2->shininess_ = 128.0f;
    material2->lightPosition_ = vec3(0.5f, 0.0f, 5.0f);
    auto cube2 = std::make_shared<Cube>(material2);
    cube2->position_ = ONE * 2.0f;
    cube2->scale_ *= 2;
    cube2->GetModel()->GetMaterial()->alpha_ = 0.5;
    viewport->scene_->AddEntity(cube2);

    // // TODO: material3 does not render consistently and sometimes appears black
    auto material3 = std::make_shared<PhongCol>(litColShader);
    material3->diffuse_ = BLUE;
    material3->specular_ = RED;
    material3->shininess_ = 128.0f;
    material3->lightPosition_ = vec3(0.5f, 0.0f, 5.0f);
    auto cube3 = std::make_shared<Cube>(material3);
    cube3->position_ = -ONE * 2.0f;
    cube3->scale_ *= 2;
    // cube5->material_->alpha_ = 0.5;
    viewport->scene_->AddEntity(cube3);

    // vp.reset();
    // material.reset();
    // cube2.reset();
    // cube4.reset();
    // cube5.reset();

    viewport->scene_->camera_->LookAt(ZERO);
  }

  virtual void Update(float deltaTime) {
    viewports_[0]->scene_->camera_->Update(deltaTime_);
    Application::Update(deltaTime);
  }
};

int main() {
  App app;

  app.Init();

  app.Run();

  app.Terminate();

  return 0;
}
