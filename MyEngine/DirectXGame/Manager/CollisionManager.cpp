#include "CollisionManager.h"


CollisionManager::CollisionManager() {
}

CollisionManager::~CollisionManager() {
}

void CollisionManager::UpDate() {
	ClearCollider();

	SetCollider();

	CheckAllCollisions();
}

void CollisionManager::ClearCollider() {
	colliders_.clear();
}

void CollisionManager::SetCollider() {

	//自弾リストの取得
	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullets();

	//コライダーをリストに登録
	colliders_.push_back(player_);
	for (auto enemyIt = enemys_->begin(); enemyIt != enemys_->end(); enemyIt++) {
		auto& enemy = *enemyIt;
		colliders_.push_back(enemy.get());
	}
	//自弾すべて
	for (auto& bullet : playerBullets) {
		colliders_.push_back(bullet.get());
	}
	//敵弾すべて
	for (auto bulletIt = enemyBullets_->begin(); bulletIt != enemyBullets_->end();bulletIt++) {
		auto& bullet = *bulletIt;
		colliders_.push_back(bullet.get());
	}
}

void CollisionManager::CheckAllCollisions() {
	std::list<Collider*>::iterator itrA = colliders_.begin();
	for (; itrA != colliders_.end(); ++itrA) {
		auto colliderA = *itrA;

		std::list<Collider*>::iterator itrB = itrA;
		itrB++;
		for (; itrB != colliders_.end(); ++itrB) {
			auto colliderB = *itrB;

			CheckCollisionPair(colliderA, colliderB);
		}
	}
}

void CollisionManager::CheckCollisionPair(Collider* colliderA, Collider* colliderB) {

	if ((colliderA->GetCollisionAttribute() & colliderB->GetCollisionMask()) == 0 || (colliderA->GetCollisionMask() & colliderB->GetCollisionAttribute()) == 0) {
		return;
	}

	Vector3 posA = colliderA->GetWorldPos();
	Vector3 posB = colliderB->GetWorldPos();
	float length = Length(posA, posB);

	if (length <= colliderA->GetRadius() + colliderB->GetRadius()) {
		colliderA->OnCollision();
		colliderB->OnCollision();
	}
}