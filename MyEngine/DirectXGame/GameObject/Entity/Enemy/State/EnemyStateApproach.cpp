#include "EnemyStateApproach.h"
#include "DirectXGame/GameObject/Entity/Enemy/Enemy.h"

void EnemyStateApproach::Update(Enemy* enemy_) {

	if (enemy_->GetBulletCoolDown() <= 0) {
		enemy_->SetBulletCoolDown(60);
		enemy_->PopBullet();
	}
	else {
		enemy_->SetBulletCoolDown(enemy_->GetBulletCoolDown() - 1);
	}

	enemy_->MovePos({0, 0, -0.5f});
	if (enemy_->GetPos().z <= 0) {
		enemy_->ChangePhase(new EnemyStateLeave());
	}

}
