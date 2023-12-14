#pragma once
#include "DirectXGame/Data/RenderItem.h"
#include "DirectXGame/Manager/TextureManager.h"
#include "DirectXGame/Manager/AudioManager.h"
#include "DirectXGame/Manager/RandomManager.h"
#include "DirectXGame/Manager/InputManager.h"
#include "DirectXGame/Manager/ImGuiManager.h"
#include "DirectXGame/Object/Model.h"
#include "DirectXGame/GameObject/Entity/Player/PlayerBullet.h"

class Player
{
public:
	Player();
	~Player();
	
	void Initialize();

	void Update();

	void Draw();

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
};

