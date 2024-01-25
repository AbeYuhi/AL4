#pragma once
#include "DirectXGame/Manager/TextureManager.h"
#include "DirectXGame/Manager/ImGuiManager.h"
#include "DirectXGame/Manager/InputManager.h"
#include "DirectXGame/Manager/AudioManager.h"
#include "DirectXGame/GameObject/Camera/MainCamera.h"
#include "DirectXGame/GameObject/Camera/SpriteCamera.h"

enum GameScene {
	TITLE, INGAME, MENU, GAMEOVER, GAMECLEAR, SCENENUM
};

class IScene
{
public:
	IScene() = default;
	virtual ~IScene() = default;

	virtual void Initialize() = 0;

	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual void Finalize() = 0;

	inline int GetSceneNo() { return sceneNo_; }

	//画像ハンドル
	static uint32_t uvCheckerHandle_;
	static uint32_t whiteTextureHandle_;

protected:
	static bool debugMode_;
	static int sceneNo_;
};