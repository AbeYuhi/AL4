#include "GameClearScene.h"

GameClearScene::GameClearScene() {}
GameClearScene::~GameClearScene() {}

void GameClearScene::Finalize() {
	
}

void GameClearScene::Initialize() {
	sceneNo_ = GAMECLEAR;

	input_ = InputManager::GetInstance();

	//スプライトカメラの更新
	SpriteCamera::GetInstance()->Initialize();

	titleTextureHandle_ = TextureManager::Load("gameClear.png");
	pushATexturehandle_ = TextureManager::Load("pushAButton.png");

	titleSprite_ = Sprite::Create({ 1280, 720 }, titleTextureHandle_);
	pushAButtonSprite_ = Sprite::Create({ 1280, 720 }, pushATexturehandle_);

	titleInfo.Initialize(true);
	pushInfo.Initialize(true);
}

void GameClearScene::Update() {
	//スプライトカメラの更新
	SpriteCamera::GetInstance()->Update();

	if (input_->IsTriggerGamePadbutton(XINPUT_GAMEPAD_A)) {
		sceneNo_ = TITLE;
	}

	titleInfo.Update();
	pushInfo.Update();
}

void GameClearScene::Draw() {
	titleSprite_->Draw(titleInfo);
	pushAButtonSprite_->Draw(pushInfo);
}