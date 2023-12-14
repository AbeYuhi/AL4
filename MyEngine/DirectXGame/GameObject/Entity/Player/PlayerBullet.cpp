#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(){}
PlayerBullet::~PlayerBullet(){}

void PlayerBullet::Initialize(Vector3 pos, Vector3 velocity){
	input_ = InputManager::GetInstance();;
	audioManager_ = AudioManager::GetInstance();
	randomManager_ = RandomManager::GetInstance();

	//テクスチャの読み込み
	model_ = Model::Create();
	modelinfo_.Initialize();
	modelinfo_.worldTransform_.data_.translate_ = pos;
	blackTexture_ = TextureManager::Load("black2x2.png");

	deadCount_ = 120;
	isDead_ = false;
	
	velocity_ = velocity;
}

void PlayerBullet::Update(){
	deadCount_--;
	if (deadCount_ <= 0) {
		isDead_ = true;
	}

	modelinfo_.worldTransform_.data_.translate_ += velocity_;

	modelinfo_.Update();
}

void PlayerBullet::Draw(){
	model_->Draw(modelinfo_, blackTexture_);
}
