#pragma once
#include <memory>
#include "DirectXGame/Object/Model.h"
#include "DirectXGame/Data/RenderItem.h"

class Skydome
{
public: 
	Skydome();
	~Skydome();

	void Initialize();

	void Update();

	void Draw();

	inline void SetParent(const Matrix4x4* parent) { modelInfo_.worldTransform_.parent_ = parent; }

private:
	std::unique_ptr<Model> model_ = nullptr;
	RenderItem modelInfo_;

};

