#include "SceneTransition.h"

SceneTransition::SceneTransition(){}
SceneTransition::~SceneTransition(){}

void SceneTransition::Initialize(){

	transitionT_ = 0;
	texture_ = TextureManager::Load();
	sprite_ = Sprite::Create({1280, 720}, texture_);
	spriteInfo_.Initialize(true);
	spriteInfo_.materialInfo_.material_->color = { 0.0f, 0.0f, 0.0f, 1.0f };
	isTransition_ = true;
	isAdd_ = true;
}

void SceneTransition::Update(){
	
	const float addT = 0.015f;
	if (isAdd_) {
		transitionT_ += addT;
		spriteInfo_.materialInfo_.material_->color.w = transitionT_ * (1.0f);
	}
	else {
		transitionT_ -= addT;
		spriteInfo_.materialInfo_.material_->color.w = transitionT_ * (1.0f);
	}

	if (transitionT_ >= 1.0f) {
		isAdd_ = false;
	}

	if (!isAdd_ && transitionT_ <= 0.0f) {
		spriteInfo_.materialInfo_.material_->color.w = 0;
		isTransition_ = false;
	}

	spriteInfo_.Update();
}

void SceneTransition::Draw(){

	sprite_->Draw(spriteInfo_);

}
