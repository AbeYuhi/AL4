#pragma once

class Enemy;

class BaseEnemyState
{
public:

	virtual void Update(Enemy* enemy_) = 0;

protected:
};

