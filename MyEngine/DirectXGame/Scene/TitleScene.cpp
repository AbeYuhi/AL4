#include "TitleScene.h"

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {}

void TitleScene::Finalize() {

}

void TitleScene::Initialize() {
	sceneNo_ = TITLE;

	SpriteCamera::GetInstance()->Initialize();

}

void TitleScene::Update() {
	SpriteCamera::GetInstance()->Update();

	if (InputManager::GetInstance()->IsTriggerKey(DIK_SPACE)) {
		sceneNo_ = INGAME;
	}

}

void TitleScene::Draw() {

}