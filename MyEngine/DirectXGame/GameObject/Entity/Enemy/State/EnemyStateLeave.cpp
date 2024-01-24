#include "EnemyStateLeave.h"
#include "DirectXGame/GameObject/Entity/Enemy/Enemy.h"

void EnemyStateLeave::Update(Enemy* enemy_) {

	enemy_->MovePos({ 0, 0, 0.75f });
	if (enemy_->GetPos().z >= 50) {
		enemy_->Fire();
		enemy_->ChangePhase(new EnemyStateApproach());
	}
}