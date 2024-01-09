#include "TitleScene.h"

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {}

void TitleScene::Finalize() {

}

void TitleScene::Initialize() {
	sceneNo_ = TITLE;

	input_ = InputManager::GetInstance();

	//スプライトカメラの更新
	SpriteCamera::GetInstance()->Initialize();

	titleTextureHandle_ = TextureManager::Load("title.png");
	pushATexturehandle_ = TextureManager::Load("pushAButton.png");

	titleSprite_ = Sprite::Create({1280, 720}, titleTextureHandle_);
	pushAButtonSprite_ = Sprite::Create({ 1280, 720 }, pushATexturehandle_);

	titleInfo.Initialize(true);
	pushInfo.Initialize(true);
}

void TitleScene::Update() {
	//スプライトカメラの更新
	SpriteCamera::GetInstance()->Update();

	if (input_->IsTriggerGamePadbutton(XINPUT_GAMEPAD_A)) {
		sceneNo_ = INGAME;
	}
	
	titleInfo.Update();
	pushInfo.Update();
}

void TitleScene::Draw() {
	titleSprite_->Draw(titleInfo);
	pushAButtonSprite_->Draw(pushInfo);
}