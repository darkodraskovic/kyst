#include "CameraComponent.h"

#include "../../Application.h"
#include "../Entity.h"
#include "../Scene.h"

namespace Kyst {

CameraComponent::CameraComponent() {
  for (int key = CAM_FORWARD; key <= CAM_ZOOM; key++) {
    CameraMovement movement = static_cast<CameraMovement>(key);
    movement_.insert({movement, 0});
  }
}

void CameraComponent::SetCamera(std::shared_ptr<Camera> camera) { camera_ = camera; }

Camera* CameraComponent::GetCamera() { return camera_.get(); }

void CameraComponent::Translate(float deltaTime) {
  float velocity = translationSpeed_ * deltaTime;

  if (camera_->GetPerspective()) {
    if (movement_.at(CAM_FORWARD)) entity_->position_ += camera_->front_ * velocity;
    if (movement_.at(CAM_BACKWARD)) entity_->position_ -= camera_->front_ * velocity;
  } else {
    camera_->zoom_ -= movement_.at(CAM_FORWARD) * zoomSpeed_;
    camera_->zoom_ += movement_.at(CAM_BACKWARD) * zoomSpeed_;
  }
  if (movement_.at(CAM_LEFT)) entity_->position_ -= camera_->right_ * velocity;
  if (movement_.at(CAM_RIGHT)) entity_->position_ += camera_->right_ * velocity;
  if (movement_.at(CAM_UP)) entity_->position_ += camera_->up_ * velocity;
  if (movement_.at(CAM_DOWN)) entity_->position_ -= camera_->up_ * velocity;
}

void CameraComponent::Rotate(bool constrainPitch) {
  if (camera_->GetPerspective()) {
    entity_->rotation_.y += movement_.at(CAM_ROT_X) * rotationSpeed_;
    entity_->rotation_.x -= movement_.at(CAM_ROT_Y) * rotationSpeed_;

    if (constrainPitch) {
      entity_->rotation_.x = clamp(entity_->rotation_.x, -89.0f, 89.0f);
    }

    camera_->SetCameraVectors(entity_->rotation_);
  } else {
    // TODO: Implement ortho cam rotation
  }
}

void CameraComponent::Zoom() {
  camera_->zoom_ -= movement_.at(CAM_ZOOM) * zoomSpeed_;
  camera_->zoom_ = clamp(camera_->zoom_, .5f, 2.0f);
}

void CameraComponent::UpdateMovementMap() {
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
}
void CameraComponent::Update(float deltaTime) {
  UpdateMovementMap();

  Translate(deltaTime);
  Rotate();
  Zoom();
}

}  // namespace Kyst
