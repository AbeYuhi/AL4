#include "Player.h"

Player::Player(){}
Player::~Player(){}

void Player::Initialize() {
	input_ = InputManager::GetInstance();;
	audioManager_ = AudioManager::GetInstance();
	randomManager_ = RandomManager::GetInstance();
	
	//テクスチャの読み込み
	model_ = Model::Create();
	modelinfo_.Initialize();
	playerTexture_ = TextureManager::Load("dog.png");

	modelinfo_.worldTransform_.data_.translate_.z = 50;

	//バレット関連
	bulletCooldown_ = 0;
}

void Player::Update() {
	
	ImGui::Begin("Player");
	ImGui::SliderFloat3("pos", &modelinfo_.worldTransform_.data_.translate_.x, -10, 10);
	ImGui::End();

	Vector3 move = { 0, 0 };
	if (input_->IsPushKey(DIK_A)) {
		move.x -= 0.2f;
	}
	if (input_->IsPushKey(DIK_D)) {
		move.x += 0.2f;
	}
	if (input_->IsPushKey(DIK_W)) {
		move.y += 0.2f;
	}
	if (input_->IsPushKey(DIK_S)) {
		move.y -= 0.2f;
	}

	Vector3 rotate = { 0, 0, 0 };
	if (input_->IsPushKey(DIK_LEFT)) {
		rotate.y -= 0.03f;
	}
	if (input_->IsPushKey(DIK_RIGHT)) {
		rotate.y += 0.03f;
	}

	modelinfo_.worldTransform_.data_.translate_ += move;
	modelinfo_.worldTransform_.data_.rotate_ += rotate;

	if (modelinfo_.worldTransform_.data_.translate_.x <= -10 || modelinfo_.worldTransform_.data_.translate_.x >= 10) {
		modelinfo_.worldTransform_.data_.translate_.x -= move.x;
	}
	if (modelinfo_.worldTransform_.data_.translate_.y <= -5 || modelinfo_.worldTransform_.data_.translate_.y >= 5) {
		modelinfo_.worldTransform_.data_.translate_.y -= move.y;
	}

	Attack();

	modelinfo_.Update();
}

void Player::Draw() {
	model_->Draw(modelinfo_, playerTexture_);
	for (auto& bullet : bullets_) {
		bullet->Draw();
	}
}

void Player::Attack() {
	const float kBulletSpeed = 1.0f;

	if (input_->IsTriggerKey(DIK_SPACE)) {
		Vector3 velocity = {0, 0, kBulletSpeed};
		velocity = TransformNormal(velocity, modelinfo_.worldTransform_.worldMatrix_);

		std::unique_ptr<PlayerBullet> bullet = std::make_unique<PlayerBullet>();
		bullet->Initialize(modelinfo_.worldTransform_.GetWorldPos(), velocity);
		bullets_.push_back(std::move(bullet));
	}

	for (auto itBullet = bullets_.begin(); itBullet != bullets_.end();) {
		PlayerBullet* bullet = itBullet->get();

		if (bullet->GetIsDead()) {
			itBullet = bullets_.erase(itBullet);
			continue;
		}

		bullet->Update();
		itBullet++;
	}
}

void Player::OnCollision() {

}