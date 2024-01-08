#include "GameClearScene.h"

GameClearScene::GameClearScene() {}
GameClearScene::~GameClearScene() {}

void GameClearScene::Finalize() {
	
}

void GameClearScene::Initialize() {
	sceneNo_ = GAMECLEAR;

	input_ = InputManager::GetInstance();

}

void GameClearScene::Update() {
	if (input_->IsTriggerGamePadbutton(XINPUT_GAMEPAD_A)) {
		sceneNo_ = TITLE;
	}

}

void GameClearScene::Draw() {

}