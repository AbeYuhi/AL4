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
	enemyTexture_ = TextureManager::Load("Slime.png");

	baseEnemyState_.reset(new EnemyStateApproach());
}

void Enemy::Update(){

	baseEnemyState_->Update(this);

	for (auto timeCallIt = timeCalls_.begin(); timeCallIt != timeCalls_.end();) {
		TimeCall* timeCall = timeCallIt->get();

		if (timeCall->IsFinished()) {
			timeCallIt = timeCalls_.erase(timeCallIt);
		}
		else {
			timeCall->Update();
			timeCallIt++;
		}
	}

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

void Enemy::Fire() {
	//
	PopBullet();

	std::function<void(void)> callBack = std::bind(&Enemy::Fire, this);
	std::unique_ptr<TimeCall> timeCall = std::make_unique<TimeCall>(callBack, 60);
	timeCalls_.push_back(std::move(timeCall));
}

void Enemy::PopBullet() {
	const float bulletSpeed = 1.0f;

	Vector3 playerWorldPos = player_->GetWorldPos();
	Vector3 enemyWorldPos = modelinfo_.worldTransform_.GetWorldPos();
	Vector3 vector = playerWorldPos - enemyWorldPos;
	vector = Normalize(vector);
	vector *= bulletSpeed;


	std::unique_ptr<EnemyBullet> bullet = std::make_unique<EnemyBullet>();
	bullet->Initialize(modelinfo_.worldTransform_.data_.translate_, vector, player_);
	gameScene_->AddBulletEnemy(std::move(bullet));
}