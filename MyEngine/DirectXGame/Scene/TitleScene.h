#pragma once
#include "IScene.h"
#include "DirectXGame/Object/Sprite.h"

class TitleScene : public IScene
{
public:
	TitleScene();
	~TitleScene();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

private:

	std::unique_ptr<Sprite> titleSprite_;
	std::unique_ptr<Sprite> pushSpaceSprite_;
	RenderItem titleSpriteinfo_;
	RenderItem pushSpaceSpriteInfo_;
	uint32_t titleTexture_;
	uint32_t pushSpaceTexture_;
	int flashingSpriteTime_;
};