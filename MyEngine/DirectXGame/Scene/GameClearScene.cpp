#include "GameClearScene.h"

GameClearScene::GameClearScene() {}
GameClearScene::~GameClearScene() {}

void GameClearScene::Finalize() {
	
}

void GameClearScene::Initialize() {
	GAMECLEAR;

}

void GameClearScene::Update() {

	if (InputManager::GetInstance()->IsPushGamePadbutton(XINPUT_GAMEPAD_A)) {
		sceneNo_ = TITLE;
	}

}

void GameClearScene::Draw() {

}