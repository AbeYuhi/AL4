#include "GameOverScene.h"

GameOverScene::GameOverScene() {}

GameOverScene::~GameOverScene() {}

void GameOverScene::Finalize() {

}

void GameOverScene::Initialize() {
	sceneNo_ = GAMEOVER;

}

void GameOverScene::Update() {
	if (input_->IsTriggerGamePadbutton(XINPUT_GAMEPAD_A)) {
		sceneNo_ = TITLE;
	}

}

void GameOverScene::Draw() {

}