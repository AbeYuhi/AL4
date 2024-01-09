#pragma once
#include "IScene.h"
#include "DirectXGame/Manager/InputManager.h"
#include "DirectXGame/GameObject/Camera/SpriteCamera.h"
#include "DirectXGame/Object/Sprite.h"
#include "DirectXGame/Object/Plane.h"
#include "DirectXGame/Object/Sphere.h"
#include "DirectXGame/Object/Model.h"

class GameOverScene : public IScene
{
public:
	GameOverScene();
	~GameOverScene();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

private:
	InputManager* input_;

	std::unique_ptr<Sprite> titleSprite_ = nullptr;
	uint32_t titleTextureHandle_;
	RenderItem titleInfo;

	std::unique_ptr<Sprite> pushAButtonSprite_ = nullptr;
	uint32_t pushATexturehandle_;
	RenderItem pushInfo;
};