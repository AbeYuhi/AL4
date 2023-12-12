#include "Player.h"

Player::Player(){}
Player::~Player(){}

void Player::Initialize() {
	
	//テクスチャの読み込み
	model_ = Model::Create("box");
	modelinfo_.Initialize();
}

void Player::Update() {
	

	modelinfo_.Update();
}

void Player::Draw() {
	model_->Draw(modelinfo_);
}
