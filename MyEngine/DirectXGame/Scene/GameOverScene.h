#pragma once
#include "IScene.h"
#include "DirectXGame/Manager/InputManager.h"

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

};