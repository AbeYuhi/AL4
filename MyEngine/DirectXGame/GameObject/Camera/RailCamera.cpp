#include "RailCamera.h"

RailCamera::RailCamera() {}

RailCamera::~RailCamera() {}

void RailCamera::Initialize(Vector3 position, Vector3 rotate) {
	worldTransform_.Initialize(false);
	worldTransform_.data_.translate_ = position;
	worldTransform_.data_.rotate_ = rotate;
	worldTransform_.UpdateWorld();

	//カメラが切り取る範囲
	nearClip_ = 0.1f;
	farClip_ = 1000.0f;
	fovY_ = 0.45f;
}


void RailCamera::Update(Vector3 translation, Vector3 rotate) {

	worldTransform_.data_.translate_ = translation;
	worldTransform_.data_.rotate_ = rotate;

	worldTransform_.UpdateWorld();
	viewMatrix_ = Inverse(worldTransform_.worldMatrix_);
	projectionMatrix_ = MakePerspectiveFovMatrix(fovY_, (float)WinApp::kWindowWidth / (float)WinApp::kWindowHeight, nearClip_, farClip_);
	viewProjectionMatrix_ = Multiply(viewMatrix_, projectionMatrix_);

	ImGui::Begin("Camera");
	ImGui::SliderFloat3("position", &worldTransform_.data_.translate_.x, -500, 500);
	ImGui::SliderFloat3("rotation", &worldTransform_.data_.rotate_.x, -2.0f * 3.14f, 2.0f * 3.14f);
	ImGui::End();
}