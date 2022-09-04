#include "Cube.h"
#include "Engine/Application.h"
#include "Engine/Graphics/Framebuffer.h"
#include "Engine/Graphics/PhongCol.h"
#include "Engine/Graphics/PhongMap.h"
#include "Engine/Scene/Component/CameraComponent.h"
#include "Engine/Scene/Component/ModelComponent.h"
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
    viewport->GetScene()->camera_->position_.z = 12.0f;
    viewport->AddEffect("Shaders/Effects/Noop.fs");
    // viewport->AddEffect("Shaders/Effects/Remove.fs");
    // viewport->AddEffect("Shaders/Effects/Inversion.fs");

    unsigned int diffuseBricks = GetResourceManager().LoadTexture("Assets/bricks_diffuse.jpg");
    unsigned int specularBricks = GetResourceManager().LoadTexture("Assets/bricks_specular.jpg");
    unsigned int emissiveBricks = GetResourceManager().LoadTexture("Assets/bricks_emissive_green.png");
    unsigned int diffuseMetal = GetResourceManager().LoadTexture("Assets/metal_diffuse.jpg");
    unsigned int specularMetal = GetResourceManager().LoadTexture("Assets/metal_specular.jpg");
    unsigned int emissiveMetal = GetResourceManager().LoadTexture("Assets/metal_emissive_red.png");

    auto litTexShader = std::make_shared<Shader>("Shaders/LitTex.vs", "Shaders/LitTex.fs");
    auto litColShader = std::make_shared<Shader>("Shaders/LitCol.vs", "Shaders/LitCol.fs");

    int size = 320;
    auto vp = Viewport::Create(true, size, size);
    vp->AddEffect("Shaders/Textures/Tex2D.fs");
    vp->AddEffect("Shaders/Effects/Inversion.fs");
    vp->DrawToBuffer();

    auto material = std::make_shared<PhongMap>();
    material->SetShader(litTexShader);
    // material->diffuse_ = diffuseMetal;
    material->diffuse_ = vp->GetTexture()->GetId();
    material->emissive_ = emissiveMetal;
    material->specular_ = specularMetal;
    material->shininess_ = 1024.0f;
    material->lightPosition_ = vec3(0.5f, 0.0f, 5.0f);
    auto cube1 = std::make_shared<Cube>(material);
    cube1->scale_ *= 2;
    viewport->GetScene()->AddEntity(cube1);

    auto material2 = std::make_shared<PhongMap>();
    material2->SetShader(litTexShader);
    material2->diffuse_ = diffuseBricks;
    material2->emissive_ = emissiveBricks;
    material2->specular_ = specularBricks;
    material2->shininess_ = 128.0f;
    material2->lightPosition_ = vec3(0.5f, 0.0f, 5.0f);
    auto cube2 = std::make_shared<Cube>(material2);
    cube2->position_ = ONE * 2.0f;
    cube2->scale_ *= 2;
    material2->alpha_ = 0.5;
    viewport->GetScene()->AddEntity(cube2);

    auto material3 = std::make_shared<PhongCol>();
    material3->SetShader(litColShader);
    material3->ambient_ = WHITE * .4f;
    material3->diffuse_ = BLUE;
    material3->specular_ = RED;
    material3->shininess_ = 128.0f;
    material3->lightPosition_ = vec3(0.5f, 0.0f, 5.0f);
    auto cube3 = std::make_shared<Cube>(material3);
    cube3->position_ = -ONE * 2.0f;
    cube3->scale_ *= 2;
    // cube3->GetModel()->GetMaterial()->alpha_ = 0.5;
    viewport->GetScene()->AddEntity(cube3);

    viewport->GetScene()->camera_->LookAt(ZERO);

    // cube3->AddComponent<ModelComponent>();
    // auto component = cube3->GetComponent<ModelComponent>();

    // cube3->AddComponent<ModelComponent>();
    // auto hasComponent = cube3->HasComponent<Updatable>();

    // cube3->AddComponent<ModelComponent>();
    // hasComponent = cube3->HasComponent<Drawable>();

    // cube3->AddComponent<CameraComponent>();
    // hasComponent = cube3->HasComponent<CameraComponent>();

    // for (auto it = cube3->components_.begin(); it != cube3->components_.end(); ++it) {
    //   auto drawable = dynamic_cast<Drawable*>((*it).get());
    //   auto updatable = dynamic_cast<Updatable*>((*it).get());
    //   std::cout << ""
    //             << "\n";
    // }
  }

  virtual void Update(float deltaTime) {
    viewports_[0]->GetScene()->camera_->Update(deltaTime_, *GetInput());
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
