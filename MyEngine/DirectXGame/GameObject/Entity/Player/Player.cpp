#include "Player.h"

Player::Player(){}
Player::~Player(){}

void Player::Initialize() {
	input_ = InputManager::GetInstance();;
	audioManager_ = AudioManager::GetInstance();
	randomManager_ = RandomManager::GetInstance();
	
	//テクスチャの読み込み
	model_ = Model::Create("Sphere");
	modelinfo_.Initialize();
	playerTexture_ = TextureManager::Load();
	reticleTexture_ = TextureManager::Load("Reticle.png");

	modelinfo_.worldTransform_.data_.translate_.z = 40;
	modelinfo_.materialInfo_.material_->enableLightint = true;

	//バレット関連
	bulletCooldown_ = 0;

	hp_ = 5;
	isDead_ = false;

	//スプライト生成
	sprite2DReticle_ = Sprite::Create({ 64, 64 }, reticleTexture_, { 0.5, 0.5 });

	info2DReticle_.Initialize(true);
	info2DReticle_.worldTransform_.data_.translate_ = {640, 360, 0};
	info2DReticle_.Update();

	info3DReticle_.Initialize(true);
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

	if (input_->GetGamePadLStick().x != 0 || input_->GetGamePadLStick().y != 0) {
		move.x = input_->GetGamePadLStick().x * 0.2f;
		move.y = input_->GetGamePadLStick().y * 0.2f;
		move.z = 0;
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

	if (modelinfo_.worldTransform_.data_.translate_.x <= -30 || modelinfo_.worldTransform_.data_.translate_.x >= 30) {
		modelinfo_.worldTransform_.data_.translate_.x -= move.x;
	}
	if (modelinfo_.worldTransform_.data_.translate_.y <= -20 || modelinfo_.worldTransform_.data_.translate_.y >= 20) {
		modelinfo_.worldTransform_.data_.translate_.y -= move.y;
	}

	Attack();

	modelinfo_.Update();


	//マウスの場合
	//POINT mousePosition;
	////マウス座標(スクリーン座標)を取得
	//GetCursorPos(&mousePosition);
	////クライアント座標に変換する
	//HWND hwnd = WinApp::GetInstance()->GetHwnd();
	//ScreenToClient(hwnd, &mousePosition);
	//sprite2DReticle_->SetPosition(Vector2((float)mousePosition.x, (float)mousePosition.y));

	//ゲームパッド
	Vector3 spritePosition = { info2DReticle_.worldTransform_.GetWorldPos().x,  info2DReticle_.worldTransform_.GetWorldPos().y, 100 };

	//ジョイスティック取得状態
	spritePosition.x += input_->GetGamePadRStick().x * 15.0f;
	spritePosition.y -= input_->GetGamePadRStick().y * 15.0f;

	info2DReticle_.worldTransform_.data_.translate_ = spritePosition;
	info2DReticle_.Update();

	//ビュープロジェクションビューポート合成行列
	Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
	Matrix4x4 matVPV = Multiply(MainCamera::GetInstance()->GetViewProjectionMatrix(), viewportMatrix);
	Matrix4x4 matInverseVPV = Inverse(matVPV);

	//スクリーン座標
	Vector3 posNear = Vector3((float)spritePosition.x, (float)spritePosition.y, 0);
	Vector3 posFar = Vector3((float)spritePosition.x, (float)spritePosition.y, 1);
	//スクリーン座標系からワールド座標系へ
	posNear = Transform(posNear, matInverseVPV);
	posFar = Transform(posFar, matInverseVPV);

	//マウスレイの方向
	Vector3 mouseDirection = posFar - posNear;
	mouseDirection = Normalize(mouseDirection);
	//カメラから照準オブジェクトの距離
	const float kDistanceTestObject = 50;
	info3DReticle_.worldTransform_.data_.translate_ = posNear + (mouseDirection * kDistanceTestObject);
	info3DReticle_.Update();
}

void Player::Draw() {
	model_->Draw(modelinfo_, playerTexture_);
	for (auto& bullet : bullets_) {
		bullet->Draw();
	}
}

void Player::DrawUI() {
	sprite2DReticle_->Draw(info2DReticle_);
}

void Player::Attack() {
	const float kBulletSpeed = 1.0f;

	if (input_->IsPushGamePadRTrigger()) {
		Vector3 velocity = info3DReticle_.worldTransform_.GetWorldPos() - modelinfo_.worldTransform_.GetWorldPos();
		velocity = Normalize(velocity);
		velocity *= kBulletSpeed;

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
	hp_--;

	if (hp_ <= 0) {
		isDead_ = true;
	}
}