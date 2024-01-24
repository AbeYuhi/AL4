#pragma once
#include "DirectXGame/Data/RenderItem.h"
#include "DirectXGame/Manager/TextureManager.h"
#include "DirectXGame/Manager/AudioManager.h"
#include "DirectXGame/Manager/RandomManager.h"
#include "DirectXGame/Manager/InputManager.h"
#include "DirectXGame/Manager/ImGuiManager.h"
#include "DirectXGame/Object/Model.h"
#include "EnemyBullet.h"
#include "DirectXGame/GameObject/Entity/Enemy/State/BaseEnemyState.h"
#include "DirectXGame/GameObject/Entity/Enemy/State/EnemyStateApproach.h"
#include "DirectXGame/GameObject/Entity/Enemy/State/EnemyStateLeave.h"
#include "DirectXGame/Sytem/TimeCall.h"

enum class Phase {
	APPROACH,
	LEAVE,
};

class Player;
class InGameScene;

class Enemy
{
public:
	Enemy();
	~Enemy();
	void Initialize();

	void Update();

	void Draw();

	void OnCollision();

	void Fire();

	void PopBullet();

public: //ゲッターセッター

	inline Vector3 GetPos() { return modelinfo_.worldTransform_.data_.translate_; }
	inline Vector3 GetWorldPos() { return modelinfo_.worldTransform_.GetWorldPos(); }
	inline void SetPos(Vector3 pos) { modelinfo_.worldTransform_.data_.translate_ = pos; }
	inline void MovePos(Vector3 pos) { modelinfo_.worldTransform_.data_.translate_ += pos; }
	inline void ChangePhase(BaseEnemyState* enemyState) { baseEnemyState_.reset(enemyState); }
	inline void SetBulletCoolDown(int coolDown) { bulletCoolDown_ = coolDown; }
	inline int GetBulletCoolDown() { return bulletCoolDown_; }
	inline bool GetIsDead() { return isDead_; }
	inline void SetIsDead(bool isDead) { isDead_ = isDead; }
	inline void SetPlayer(Player* player) { player_ = player; }
	inline void SetGameScene(InGameScene* gameScene) { gameScene_ = gameScene; }
	inline void ClearTimeCall() { timeCalls_.clear(); }

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

	//球のクールダウン
	int bulletCoolDown_;

	bool isDead_;

	Player* player_;
	InGameScene* gameScene_;

	std::list<std::unique_ptr<TimeCall>> timeCalls_;
};

