#include "GameOverScene.h"

GameOverScene::GameOverScene() {}

GameOverScene::~GameOverScene() {}

void GameOverScene::Finalize() {

}

void GameOverScene::Initialize() {
	sceneNo_ = GAMEOVER;

	input_ = InputManager::GetInstance();

	//スプライトカメラの更新
	SpriteCamera::GetInstance()->Initialize();

	titleTextureHandle_ = TextureManager::Load("gameOver.png");
	pushATexturehandle_ = TextureManager::Load("pushAButton.png");

	titleSprite_ = Sprite::Create({ 1280, 720 }, titleTextureHandle_);
	pushAButtonSprite_ = Sprite::Create({ 1280, 720 }, pushATexturehandle_);

	titleInfo.Initialize(true);
	pushInfo.Initialize(true);

}

void GameOverScene::Update() {
	//スプライトカメラの更新
	SpriteCamera::GetInstance()->Update();

	if (input_->IsTriggerGamePadbutton(XINPUT_GAMEPAD_A)) {
		sceneNo_ = TITLE;
	}

	titleInfo.Update();
	pushInfo.Update();
}

void GameOverScene::Draw() {
	titleSprite_->Draw(titleInfo);
	pushAButtonSprite_->Draw(pushInfo);
}