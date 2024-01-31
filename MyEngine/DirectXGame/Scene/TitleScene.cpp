#include "TitleScene.h"

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {}

void TitleScene::Finalize() {

}

void TitleScene::Initialize() {
	sceneNo_ = TITLE;

	SpriteCamera::GetInstance()->Initialize();

	titleTexture_ = TextureManager::Load("title.png");
	pushSpaceTexture_ = TextureManager::Load("pushSpace.png");
	titleSprite_ = Sprite::Create({1280, 720}, titleTexture_);
	pushSpaceSprite_ = Sprite::Create({ 1280, 720 }, pushSpaceTexture_);
	titleSpriteinfo_.Initialize(true);
	pushSpaceSpriteInfo_.Initialize(true);

	flashingSpriteTime_ = 0;
}

void TitleScene::Update() {
	SpriteCamera::GetInstance()->Update();

	if (InputManager::GetInstance()->IsTriggerKey(DIK_SPACE) || InputManager::GetInstance()->IsPushGamePadbutton(XINPUT_GAMEPAD_A)) {
		sceneNo_ = INGAME;
	}

	flashingSpriteTime_++;
	if (flashingSpriteTime_ >= 40) {
		flashingSpriteTime_ -= 40;
	}

	titleSpriteinfo_.Update();
	pushSpaceSpriteInfo_.Update();
}

void TitleScene::Draw() {
	titleSprite_->Draw(titleSpriteinfo_);

	if (flashingSpriteTime_ < 20) {
		pushSpaceSprite_->Draw(pushSpaceSpriteInfo_);
	}
}