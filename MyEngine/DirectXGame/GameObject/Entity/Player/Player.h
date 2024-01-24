#pragma once
#include "DirectXGame/Data/RenderItem.h"
#include "DirectXGame/Manager/TextureManager.h"
#include "DirectXGame/Manager/AudioManager.h"
#include "DirectXGame/Manager/RandomManager.h"
#include "DirectXGame/Manager/InputManager.h"
#include "DirectXGame/Manager/ImGuiManager.h"
#include "DirectXGame/Object/Model.h"
#include "DirectXGame/Object/Sprite.h"
#include "DirectXGame/GameObject/Entity/Player/PlayerBullet.h"
#include "DirectXGame/GameObject/Entity/Collider/Collider.h"
#include "DirectXGame/GameObject/Camera/MainCamera.h"

class Player : public Collider
{
public:
	Player();
	~Player();
	
	void Initialize();

	void Update();

	void Draw();

	void DrawUI();

	void OnCollision();

	inline Vector3 GetWorldPos() { return modelinfo_.worldTransform_.GetWorldPos(); }
	inline const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() const { return bullets_; }
	inline void SetParent(const Matrix4x4* parent) { modelinfo_.worldTransform_.parent_ = parent; }

private:

	void Attack();

private:
	InputManager* input_;
	AudioManager* audioManager_;
	RandomManager* randomManager_;
	
	//モデル
	std::unique_ptr<Model> model_;
	RenderItem modelinfo_;
	uint32_t playerTexture_;

	//バレット
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
	int32_t bulletCooldown_;


	//レティクル
	RenderItem info2DReticle_;
	RenderItem info3DReticle_;
	std::unique_ptr<Sprite> sprite2DReticle_ = nullptr;
	uint32_t reticleTexture_;
};

