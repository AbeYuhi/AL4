#include "SceneManager.h"

SceneManager* SceneManager::GetInstance() {
	static SceneManager instance;
	return &instance;
}

void SceneManager::Initialize(GameScene gameScene){

	//シーンファクトリー
	sceneFactory_ = SceneFactory::GetInstance();

	//初期シーン
	sceneNo_ = gameScene;
	//初期ゲームシーンの初期化
	scene_ = sceneFactory_->CreateScene((GameScene)sceneNo_);

	//初期シーンの初期化
	scene_->Initialize();

	sceneTransition_ = std::make_unique<SceneTransition>();
	sceneTransition_->SetIsTransition(false);
}

void SceneManager::Update() {
	preSceneNo_ = sceneNo_;
	sceneNo_ = scene_->GetSceneNo();
	ImGui::Begin("GameScene");
	const char* modes[] = { "Title", "InGame", "Menu", "GameOver", "GameClear" };
	ImGui::Combo("gameScene", &sceneNo_, modes, IM_ARRAYSIZE(modes));
	ImGui::End();
	if (preSceneNo_ != sceneNo_) {
		//シーンの削除
		scene_->Finalize();
		scene_.reset();
		//シーンの生成
		scene_ = sceneFactory_->CreateScene((GameScene)sceneNo_);
		//シーンの初期化
		scene_->Initialize();
		//画面遷移の初期化
		sceneTransition_.reset();
		sceneTransition_ = std::make_unique<SceneTransition>();
		sceneTransition_->Initialize();
	}

	if (sceneTransition_->IsTransition()) {
		sceneTransition_->Update();
		if (!sceneTransition_->IsTransition()) {
			scene_->Update();
		}
	}
	else {
		//シーンの更新
		scene_->Update();
	}
}

void SceneManager::Draw() {
	if (sceneTransition_->IsTransition()) {
		sceneTransition_->Draw();
	}
	else {
		//シーンの描画
		scene_->Draw();
	}
}
