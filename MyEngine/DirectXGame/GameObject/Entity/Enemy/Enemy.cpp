#include "Enemy.h"
#include "DirectXGame/GameObject/Entity/Player/Player.h"
#include "DirectXGame/Scene/InGameScene.h"

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

	bulletCoolDown_ = 0;
	isDead_ = false;

	//テクスチャ
	enemyTexture_ = TextureManager::Load();
	modelinfo_.materialInfo_.material_->color = {0, 0, 0, 1};

	baseEnemyState_.reset(new EnemyStateApproach());
}

void Enemy::Update(){

	baseEnemyState_->Update(this);

	modelinfo_.Update();

	if (modelinfo_.worldTransform_.GetWorldPos().z <= -10) {
		isDead_ = true;
	}

}

void Enemy::Draw(){
	model_->Draw(modelinfo_, enemyTexture_);
}

void Enemy::OnCollision() {
	isDead_ = true;
}

void Enemy::PopBullet() {
	const float bulletSpeed = 1.0f;

	Vector3 playerWorldPos = player_->GetWorldPos();
	Vector3 enemyWorldPos = modelinfo_.worldTransform_.GetWorldPos();
	Vector3 vector = playerWorldPos - enemyWorldPos;
	vector = Normalize(vector);
	vector *= bulletSpeed;


	std::unique_ptr<EnemyBullet> bullet = std::make_unique<EnemyBullet>();
	bullet->Initialize(modelinfo_.worldTransform_.data_.translate_, vector);
	gameScene_->AddBulletEnemy(std::move(bullet));
}