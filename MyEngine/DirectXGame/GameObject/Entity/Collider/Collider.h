#pragma once
#include "DirectXGame/Math/Vector3.h"

class Collider
{
public:
	Collider();
	~Collider();

	virtual void OnCollision() = 0;

	virtual Vector3 GetWorldPos() = 0;

	inline float GetRadius() { return radius; }
	inline void SetRadius(float radius) { this->radius = radius; }

private:
	float radius = 2;
};