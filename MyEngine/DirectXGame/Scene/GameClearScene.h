#pragma once
#include "IScene.h"
#include "DirectXGame/Manager/InputManager.h"

class GameClearScene : public IScene
{
public:
	GameClearScene();
	~GameClearScene();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Finalize() override;
private:
	InputManager* input_;

};