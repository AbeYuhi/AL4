#include "EnemyBullet.h"
#include "DirectXGame/GameObject/Entity/Player/Player.h"

EnemyBullet::EnemyBullet() {}
EnemyBullet::~EnemyBullet() {}

void EnemyBullet::Initialize(Vector3 pos, Vector3 velocity, Player* player) {
	input_ = InputManager::GetInstance();;
	audioManager_ = AudioManager::GetInstance();
	randomManager_ = RandomManager::GetInstance();
	player_ = player;

	//テクスチャの読み込み
	model_ = Model::Create();
	modelinfo_.Initialize();
	modelinfo_.worldTransform_.data_.translate_ = pos;
	modelinfo_.worldTransform_.data_.scale_ = {0.5f, 0.5f, 3.0f};
	modelinfo_.materialInfo_.material_->color = { 1.0f, 0.0, 0.0f, 1.0f };
	bulletTexture_ = TextureManager::Load();

	deadCount_ = 120;
	isDead_ = false;

	velocity_ = velocity;

	modelinfo_.worldTransform_.data_.rotate_.y = std::atan2(velocity_.x, velocity_.z);
	float widthLength = Length({ velocity_.x, 0, velocity_.z });
	modelinfo_.worldTransform_.data_.rotate_.x = std::atan2(-velocity_.y, widthLength);

	//衝突属性を設定
	SetCollisionAttribute(kCollisionAttributeEnemy);
	SetCollisionMask(~kCollisionAttributeEnemy);
}

void EnemyBullet::Update() {
	deadCount_--;
	if (deadCount_ <= 0) {
		isDead_ = true;
	}

	Vector3 toPlayer = player_->GetWorldPos() - modelinfo_.worldTransform_.GetWorldPos();

	toPlayer = Normalize(toPlayer);
	velocity_ = Normalize(velocity_);

	velocity_ = Slerp(velocity_, toPlayer, 0.15f) * 2;

	modelinfo_.worldTransform_.data_.rotate_.y = std::atan2(velocity_.x, velocity_.z);
	float widthLength = Length({ velocity_.x, 0, velocity_.z });
	modelinfo_.worldTransform_.data_.rotate_.x = std::atan2(-velocity_.y, widthLength);

	modelinfo_.worldTransform_.data_.translate_ += velocity_;

	modelinfo_.Update();
}

void EnemyBullet::Draw() {
	model_->Draw(modelinfo_, bulletTexture_);
}

void EnemyBullet::OnCollision() {
	isDead_ = true;
}