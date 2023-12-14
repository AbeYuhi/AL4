#pragma once
#include "DirectXGame/Data/RenderItem.h"
#include "DirectXGame/Manager/TextureManager.h"
#include "DirectXGame/Manager/AudioManager.h"
#include "DirectXGame/Manager/RandomManager.h"
#include "DirectXGame/Manager/InputManager.h"
#include "DirectXGame/Manager/ImGuiManager.h"
#include "DirectXGame/Object/Model.h"
#include "DirectXGame/GameObject/Entity/Enemy/State/BaseEnemyState.h"
#include "DirectXGame/GameObject/Entity/Enemy/State/EnemyStateApproach.h"
#include "DirectXGame/GameObject/Entity/Enemy/State/EnemyStateLeave.h"

enum class Phase {
	APPROACH,
	LEAVE,
};

class Enemy
{
public:
	Enemy();
	~Enemy();
	void Initialize();

	void Update();

	void Draw();

private:

	void Approach();

	void Leave();

public: //ゲッターセッター

	inline Vector3 GetPos() { return modelinfo_.worldTransform_.data_.translate_; }
	inline void SetPos(Vector3 pos) { modelinfo_.worldTransform_.data_.translate_ = pos; }
	inline void MovePos(Vector3 pos) { modelinfo_.worldTransform_.data_.translate_ += pos; }
	inline void ChangePhase(BaseEnemyState* enemyState) { baseEnemyState_.reset(enemyState); }

private:
	InputManager* input_;
	AudioManager* audioManager_;
	RandomManager* randomManager_;

	//モデル
	std::unique_ptr<Model> model_;
	RenderItem modelinfo_;
	uint32_t enemyTexture_;

	//フェーズ
	std::unique_ptr<BaseEnemyState> baseEnemyState_;
};

