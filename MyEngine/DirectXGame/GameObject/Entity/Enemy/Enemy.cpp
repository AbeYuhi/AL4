#include "Enemy.h"

Enemy::Enemy(){}
Enemy::~Enemy(){}

void Enemy::Initialize(){
	input_ = InputManager::GetInstance();;
	audioManager_ = AudioManager::GetInstance();
	randomManager_ = RandomManager::GetInstance();

	//モデルの生成
	model_ = Model::Create();
	modelinfo_.Initialize();
	modelinfo_.worldTransform_.data_.translate_.y = 2;
	modelinfo_.worldTransform_.data_.translate_.z = 50;

	//テクスチャ
	enemyTexture_ = TextureManager::Load("Slime.png");

	baseEnemyState_.reset(new EnemyStateApproach());
}

void Enemy::Update(){

	baseEnemyState_->Update(this);

	modelinfo_.Update();
}

void Enemy::Draw(){
	model_->Draw(modelinfo_, enemyTexture_);
}