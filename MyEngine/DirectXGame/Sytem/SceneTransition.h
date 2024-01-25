#pragma once
#include "DirectXGame/Manager/TextureManager.h"
#include "DirectXGame/Object/Sprite.h"
#include "DirectXGame/Data/RenderItem.h"
#include "DirectXGame/Math/Math.h"

class SceneTransition
{
public:
	SceneTransition();
	~SceneTransition();

	void Initialize();

	void Update();

	void Draw();

	inline bool IsTransition() { return isTransition_; }
	inline void SetIsTransition(bool isEnable) { isTransition_ = isEnable; }

private:

	std::unique_ptr<Sprite> sprite_;
	uint32_t texture_;
	RenderItem spriteInfo_;
	float transitionT_;
	bool isTransition_;
	bool isAdd_;
};

