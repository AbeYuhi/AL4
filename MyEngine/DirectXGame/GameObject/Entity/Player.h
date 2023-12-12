#pragma once
#include "DirectXGame/Data/RenderItem.h"
#include "DirectXGame/Manager/TextureManager.h"
#include "DirectXGame/Manager/InputManager.h"
#include "DirectXGame/Manager/ImGuiManager.h"
#include "DirectXGame/Object/Model.h"

class Player
{
public:
	Player();
	~Player();
	
	void Initialize();

	void Update();

	void Draw();

private:
	
	//モデル
	std::unique_ptr<Model> model_;
	uint32_t modelTextureHandle_;
	RenderItem modelinfo_;

};

