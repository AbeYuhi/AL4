#include "TitleScene.h"

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {}

void TitleScene::Finalize() {

}

void TitleScene::Initialize() {
	sceneNo_ = TITLE;

	input_ = InputManager::GetInstance();

}

void TitleScene::Update() {
	if (input_->IsTriggerGamePadbutton(XINPUT_GAMEPAD_A)) {
		sceneNo_ = INGAME;
	}
	

}

void TitleScene::Draw() {

}