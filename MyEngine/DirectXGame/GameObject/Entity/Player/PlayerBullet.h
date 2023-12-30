#pragma once
#include "DirectXGame/Data/RenderItem.h"
#include "DirectXGame/Manager/TextureManager.h"
#include "DirectXGame/Manager/AudioManager.h"
#include "DirectXGame/Manager/RandomManager.h"
#include "DirectXGame/Manager/InputManager.h"
#include "DirectXGame/Manager/ImGuiManager.h"
#include "DirectXGame/Object/Model.h"

class PlayerBullet
{
public:
	PlayerBullet();
	~PlayerBullet();

	void Initialize(Vector3 pos, Vector3 velocity);

	void Update();

	void Draw();

	void OnCollision();

	inline bool GetIsDead() { return isDead_; }
	inline Vector3 GetWorldPos() { return modelinfo_.worldTransform_.GetWorldPos(); }

private:
	InputManager* input_;
	AudioManager* audioManager_;
	RandomManager* randomManager_;

	//モデル
	std::unique_ptr<Model> model_;
	RenderItem modelinfo_;
	uint32_t blackTexture_;

	Vector3 velocity_;

	int deadCount_;
	bool isDead_;
};

