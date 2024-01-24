#pragma once
#include "DirectXGame/Data/RenderItem.h"
#include "DirectXGame/Manager/TextureManager.h"
#include "DirectXGame/Manager/AudioManager.h"
#include "DirectXGame/Manager/RandomManager.h"
#include "DirectXGame/Manager/InputManager.h"
#include "DirectXGame/Manager/ImGuiManager.h"
#include "DirectXGame/Object/Model.h"

class Player;

class EnemyBullet
{
public:
	EnemyBullet();
	~EnemyBullet();

	void Initialize(Vector3 pos, Vector3 velocity, Player* player);

	void Update();

	void Draw();

	void OnCollision();

	inline bool GetIsDead() { return isDead_; }
	inline Vector3 GetWorldPos() { return modelinfo_.worldTransform_.GetWorldPos(); }
	inline Player* GetPlayer(Player* player) { player_ = player; }

private:
	InputManager* input_;
	AudioManager* audioManager_;
	RandomManager* randomManager_;
	Player* player_;

	//モデル
	std::unique_ptr<Model> model_;
	RenderItem modelinfo_;
	uint32_t bulletTexture_;

	Vector3 velocity_;

	int deadCount_;
	bool isDead_;
};

