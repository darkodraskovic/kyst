#include "CameraComponent.h"

#include "../../Application.h"
#include "../Entity.h"
#include "../Scene.h"

CameraComponent::CameraComponent() {
  for (int key = CAM_FORWARD; key <= CAM_ZOOM; key++) {
    CameraMovement movement = static_cast<CameraMovement>(key);
    movement_.insert({movement, 0});
  }
}

void CameraComponent::SetCamera(std::shared_ptr<Camera> camera) { camera_ = camera; }

Camera* CameraComponent::GetCamera() { return camera_.get(); }

void CameraComponent::Update(float deltaTime) {
  // reset movement map
  for (int key = CAM_FORWARD; key != CAM_ZOOM; key++) {
    CameraMovement movement = static_cast<CameraMovement>(key);
    movement_.at(movement) = 0;
  }

  // populate movement map
  auto* input = entity_->GetScene()->GetViewport()->GetApplication()->GetInput();
  movement_.at(CAM_FORWARD) = input->GetKey(GLFW_KEY_W);
  movement_.at(CAM_BACKWARD) = input->GetKey(GLFW_KEY_S);
  movement_.at(CAM_LEFT) = input->GetKey(GLFW_KEY_A);
  movement_.at(CAM_RIGHT) = input->GetKey(GLFW_KEY_D);
  movement_.at(CAM_UP) = input->GetKey(GLFW_KEY_E);
  movement_.at(CAM_DOWN) = input->GetKey(GLFW_KEY_Q);

  movement_.at(CAM_ROT_X) = Input::mouseData_.moveX_;
  movement_.at(CAM_ROT_Y) = Input::mouseData_.moveY_;

  movement_.at(CAM_ZOOM) = Input::mouseData_.scrollY_;

  // apply movement map
  camera_->Update(deltaTime, movement_, entity_->position_, entity_->rotation_);
}
