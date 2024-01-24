#pragma once
#include "DirectXGame/Math/Vector3.h"
#include "DirectXGame/GameObject/Entity/Collider/CollisionConfig.h"

class Collider
{
public:
	Collider();
	~Collider();

	virtual void OnCollision() = 0;

	virtual Vector3 GetWorldPos() = 0;

	inline float GetRadius() { return radius; }
	inline void SetRadius(float radius) { this->radius = radius; }

	//属性
	inline uint32_t GetCollisionAttribute() { return collisionAttribute_; }
	inline void SetCollisionAttribute(uint32_t collisionAttribute) { this->collisionAttribute_ = collisionAttribute; }
	//マスク
	inline uint32_t GetCollisionMask() { return collisionMask_; }
	inline void SetCollisionMask(uint32_t collisionMask) { this->collisionMask_ = collisionMask; }

private:
	float radius = 2;

	//衝突属性(自分)
	uint32_t collisionAttribute_ = 0xffffffff;
	//衝突マスク(相手)
	uint32_t collisionMask_ = 0xffffffff;
};