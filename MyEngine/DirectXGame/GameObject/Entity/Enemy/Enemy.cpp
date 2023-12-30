#include "Enemy.h"
#include "DirectXGame/GameObject/Entity/Player/Player.h"

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

	bulletCoolDown_ = 0;

	baseEnemyState_.reset(new EnemyStateApproach());
}

void Enemy::Update(){

	baseEnemyState_->Update(this);

	for (auto itBullet = bullets_.begin(); itBullet != bullets_.end();) {
		EnemyBullet* bullet = itBullet->get();

		if (bullet->GetIsDead()) {
			itBullet = bullets_.erase(itBullet);
			continue;
		}

		bullet->Update();
		itBullet++;
	}

	modelinfo_.Update();
}

void Enemy::Draw(){
	model_->Draw(modelinfo_, enemyTexture_);

	for (auto &bullet : bullets_) {
		bullet->Draw();
	}

}

void Enemy::PopBullet() {
	if (bulletCoolDown_ <= 0) {
		const float bulletSpeed = 1.0f;

		Vector3 playerWorldPos = player_->GetWorldPos();
		Vector3 enemyWorldPos = modelinfo_.worldTransform_.GetWorldPos();
		Vector3 vector = playerWorldPos - enemyWorldPos;
		vector = Normalize(vector);
		vector *= bulletSpeed;


		std::unique_ptr<EnemyBullet> bullet = std::make_unique<EnemyBullet>();
		bullet->Initialize(modelinfo_.worldTransform_.data_.translate_, vector);
		bullets_.push_back(std::move(bullet));
		bulletCoolDown_ = 60;
	}
	else {
		bulletCoolDown_--;
	}
}

void Enemy::OnCollision() {

}