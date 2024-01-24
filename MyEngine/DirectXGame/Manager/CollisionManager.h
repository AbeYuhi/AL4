#pragma once
#include <cstdint>
#include <concepts>
#include <compare>
#include <list>
#include "DirectXGame/GameObject/Entity/Collider/Collider.h"
#include "DirectXGame/GameObject/Entity/Player/Player.h"
#include "DirectXGame/GameObject/Entity/Player/PlayerBullet.h"
#include "DirectXGame/GameObject/Entity/Enemy/Enemy.h"
#include "DirectXGame/GameObject/Entity/Enemy/EnemyBullet.h"

class CollisionManager
{
public: //コンストラクタ、デストラクタ
	CollisionManager();
	~CollisionManager();

public: //関数

	void UpDate();

	void ClearCollider();

	void SetCollider();

	/// <summary>
	/// 衝突判定
	/// </summary>
	void CheckAllCollisions();

public: //ゲッターセッター

	inline void SetPlayer(Player* player) { player_ = player; }
	inline void SetEnemy(std::list<std::unique_ptr<Enemy>>* enemys) { enemys_ = enemys; }
	inline void SetEnemyBullet(std::list<std::unique_ptr<EnemyBullet>>* enemyBullets) { enemyBullets_ = enemyBullets; }

private:

	std::list<Collider*> colliders_;

	Player* player_;
	std::list<std::unique_ptr<Enemy>>* enemys_;
	std::list<std::unique_ptr<EnemyBullet>>* enemyBullets_;

	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);
};