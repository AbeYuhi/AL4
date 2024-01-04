#pragma once
#include <algorithm>
#include <iostream>
#include <list>
#include "DirectXGame/Manager/ImGuiManager.h"
#include "DirectXGame/Data/RenderItem.h"

class RailCamera {
public:
	RailCamera();
	~RailCamera();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Vector3 position, Vector3 rotate);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(Vector3 position, Vector3 rotate);

	inline Matrix4x4& GetWorldMatrix() { return worldTransform_.worldMatrix_; };
	inline Matrix4x4& GetProjectionMatrix() { return projectionMatrix_; };

	/// <summary>
	/// プロジェクション行列計算用のメンバ設定関数群
	/// </summary>
	void SetFovAngleY(float value) { fovY_ = value; }
	void SetNearZ(float value) { nearClip_ = value; }
	void SetFarZ(float value) { farClip_ = value; }

private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	Matrix4x4 viewMatrix_;
	Matrix4x4 projectionMatrix_;
	Matrix4x4 viewProjectionMatrix_;
	float nearClip_;
	float farClip_;
	float fovY_;
};
