#include "InGameScene.h"

InGameScene::InGameScene() {

}

InGameScene::~InGameScene() {

}

void InGameScene::Finalize() {}

void InGameScene::Initialize() {
	sceneNo_ = INGAME;

	//基本機能
	winApp_ = WinApp::GetInstance();
	directXCommon_ = DirectXCommon::GetInstance();
	input_ = InputManager::GetInstance();;
	audioManager_ = AudioManager::GetInstance();
	randomManager_ = RandomManager::GetInstance();
	mainCamera_ = MainCamera::GetInstance();
	spriteCamera_ = SpriteCamera::GetInstance();

	//デバックモード中ならdebugカメラを有効に
	isDebugCamera_ = debugMode_;

	//インゲームカメラ
	gameCamera_ = std::make_unique<InGameCamera>();
	gameCamera_->Initialize();
	//デバッグカメラ
	debugCamera_ = std::make_unique<DebugCamera>();
	debugCamera_->Initialize();
	//レールカメラ
	railCamera_ = std::make_unique<RailCamera>();
	railCamera_->Initialize({0, 0, -50}, {0, 0, 0});

	//スプライトカメラの初期化
	spriteCamera_->Initialize();

	//平行光源
	lightObj_ = std::make_unique<LightObject>();
	lightObj_->Initialize();

	//ブレンドモード
	blendMode_ = kBlendModeNormal;

	player_ = std::make_unique<Player>();
	player_->Initialize();
	player_->SetParent(mainCamera_->GetPWorldMatrix());

	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize();

	LoadEnemyPopData();

	isWait_ = false;
}

void InGameScene::Update() {
	//カメラの更新
	ImGui::Begin("Debug");
	ImGui::Checkbox("UseDebugCamera", &isDebugCamera_);
	ImGui::End();
	
	if (isDebugCamera_) {
		debugCamera_->Update();
		mainCamera_->Update(debugCamera_->GetWorldMatrix(), debugCamera_->GetProjectionMatrix());
	}
	else {
		//gameCamera_->Update();
		railCamera_->Update({0, 0, -1}, {0, 0, 0});
		mainCamera_->Update(railCamera_->GetWorldMatrix(), railCamera_->GetProjectionMatrix());
	}
	//スプライトカメラの更新
	spriteCamera_->Update();
	//ライトの更新
	lightObj_->Update();

	player_->Update();

	UpdateEnemyPopCommands();
	for (auto itEnemy = enemys_.begin(); itEnemy != enemys_.end();) {
		Enemy* enemy = itEnemy->get();

		if (enemy->GetIsDead()) {
			itEnemy = enemys_.erase(itEnemy);
			continue;
		}

		enemy->Update();
		itEnemy++;
	}

	for (auto itBullet = enemyBullets_.begin(); itBullet != enemyBullets_.end();) {
		EnemyBullet* bullet = itBullet->get();

		if (bullet->GetIsDead()) {
			itBullet = enemyBullets_.erase(itBullet);
			continue;
		}

		bullet->Update();
		itBullet++;
	}

	skydome_->Update();

	//当たり判定
	Vector3 posA, posB;
	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullets();
	const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets = enemyBullets_;

#pragma region 自キャラと敵弾の当たり判定
	posA = player_->GetWorldPos();
	for (auto& enemyBullet : enemyBullets) {
		posB = enemyBullet->GetWorldPos();

		float length = Length(posA - posB);
		if (length <= 2.0f) {
			player_->OnCollision();
			enemyBullet->OnCollision();
		}
	}
#pragma endregion

#pragma region 自弾と敵キャラの当たり判定
	for (auto& enemy : enemys_) {
		posA = enemy->GetWorldPos();
		for (auto& playerBullet : playerBullets) {
			posB = playerBullet->GetWorldPos();

			float length = Length(posA - posB);
			if (length <= 2.0f) {
				enemy->OnCollision();
				playerBullet->OnCollision();
			}
		}
	}

#pragma endregion

#pragma region 自弾と敵弾の当たり判定
	for (auto& playerBullet : playerBullets) {
		posA = playerBullet->GetWorldPos();
		for (auto& enemyBullet : enemyBullets) {
			posB = enemyBullet->GetWorldPos();

			float length = Length(posA - posB);
			if (length <= 2.0f) {
				playerBullet->OnCollision();
				enemyBullet->OnCollision();
			}
		}
	}
#pragma endregion

	ImGui::Begin("BlendMode");
	const char* modes[] = { "None", "Normal", "Add", "SubTract", "MultiPly", "Screen"};
	ImGui::Combo("blendMode", &blendMode_, modes, IM_ARRAYSIZE(modes));
	GraphicsPipelineManager::GetInstance()->SetBlendMode(static_cast<BlendMode>(blendMode_));
	ImGui::End();
}

void InGameScene::Draw() {
	//カメラの転送
	mainCamera_->Draw();
	//ライティングの転送
	lightObj_->Draw();

	///背景スプライトの描画開始


	///背景スプライト描画終了
	//深度バッファのクリア
	directXCommon_->ClearDepthStencilBuffer();

	///前面スプライトの描画開始

	player_->DrawUI();

	///前面スプライトの描画終了

	///オブジェクトの描画開始

	player_->Draw();
	for (auto& enemy : enemys_) {
		enemy->Draw();
	}

	for (auto& bullet : enemyBullets_) {
		bullet->Draw();
	}

	skydome_->Draw();

	///オブジェクトの描画終了

	///パーティクルの描画

	

	///パーティクルの描画終了
}

void InGameScene::AddBulletEnemy(std::unique_ptr<EnemyBullet> enemyBullet) {
	enemyBullets_.push_back(std::move(enemyBullet));
}

void InGameScene::PopEnemy(Vector3 enemyPos) {
	std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>();
	enemy->Initialize();
	enemy->SetPlayer(player_.get());
	enemy->SetGameScene(this);
	enemy->SetPos(enemyPos);
	enemys_.push_back(std::move(enemy));
}

void InGameScene::LoadEnemyPopData() {
	//ファイルを開く
	std::ifstream file;
	file.open("Resources/ScriptFilles/enemyPop.csv");
	assert(file.is_open());
	//ファイルの内容を文字列ストリームにコピー
	enemyPopCommands_ << file.rdbuf();

	//ファイルを閉じる
	file.close();
}

void InGameScene::UpdateEnemyPopCommands() {
	//待機処理中
	if (isWait_) {
		waitTime_--;
		if (waitTime_ < 0) {
			isWait_ = false;
		}
		return;
	}

	//1行分の文字列を入れる変数
	std::string line;
	//コマンド実行ループ
	while (getline(enemyPopCommands_, line)) {
		std::istringstream line_stream(line);

		std::string word;
		//,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');

		if (word.find("//") == 0) {
			//コメント行を飛ばす
			continue;
		}

		if (word.find("POP") == 0) {
			//x座標
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			//y座標
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			//z座標
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			//敵を発生させえる
			PopEnemy(Vector3(x, y, z));
		}

		if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			//待ち時間
			int32_t waitTime = atoi(word.c_str());

			//待機開始
			isWait_ = true;
			waitTime_ = waitTime;

			//コマンドループを抜ける
			break;
		}
	}
}