#include "EnemyStateApproach.h"
#include "DirectXGame/GameObject/Entity/Enemy/Enemy.h"

void EnemyStateApproach::Update(Enemy* enemy_) {

	enemy_->MovePos({0, 0, -0.5f});
	if (enemy_->GetPos().z <= 0) {
		enemy_->ClearTimeCall();
		enemy_->ChangePhase(new EnemyStateLeave());
	}

}
