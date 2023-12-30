#include "EnemyBullet.h"

EnemyBullet::EnemyBullet() {}
EnemyBullet::~EnemyBullet() {}

void EnemyBullet::Initialize(Vector3 pos, Vector3 velocity) {
	input_ = InputManager::GetInstance();;
	audioManager_ = AudioManager::GetInstance();
	randomManager_ = RandomManager::GetInstance();

	//テクスチャの読み込み
	model_ = Model::Create();
	modelinfo_.Initialize();
	modelinfo_.worldTransform_.data_.translate_ = pos;
	modelinfo_.materialInfo_.material_->color = { 1.0f, 0.0, 0.0f, 1.0f };
	bulletTexture_ = TextureManager::Load();

	deadCount_ = 120;
	isDead_ = false;

	velocity_ = velocity;
}

void EnemyBullet::Update() {
	deadCount_--;
	if (deadCount_ <= 0) {
		isDead_ = true;
	}

	modelinfo_.worldTransform_.data_.translate_ += velocity_;

	modelinfo_.Update();
}

void EnemyBullet::Draw() {
	model_->Draw(modelinfo_, bulletTexture_);
}

void EnemyBullet::OnCollision() {
	isDead_ = true;
}