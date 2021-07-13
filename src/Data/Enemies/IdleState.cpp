#include "IdleState.h"

std::shared_ptr<State> IdleState::Update(Actor& actor)
{
	auto enemy = static_cast<Enemy&>(actor);

	switch (enemy.GetEnemyType())
	{
	default:
		enemy.EnemyDefaultIdle();
		break;
	}

	return shared_from_this();
}

void IdleState::Draw(Actor& actor)
{
	auto enemy = static_cast<Enemy&>(actor);
	DrawTexture(enemy.GetTexture(), enemy.GetPosition().x, enemy.GetPosition().y, WHITE);
}
