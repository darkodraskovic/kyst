#include "CameraComponent.h"

#include "../../Application.h"
#include "../Entity.h"
#include "../Scene.h"

void CameraComponent::SetCamera(std::shared_ptr<Camera> camera) { camera_ = camera; }

Camera* CameraComponent::GetCamera() { return camera_.get(); }

void CameraComponent::Update(float deltaTime) {
  camera_->Update(deltaTime, entity_->GetScene()->GetViewport()->GetApplication()->GetInput());
}
