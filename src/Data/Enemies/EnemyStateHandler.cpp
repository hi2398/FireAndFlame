#include "EnemyStateHandler.h"
#include <iostream>
#include "ApproachingState.h"
#include "AttackingState.h"
#include "RoamingState.h"
#include "IdleState.h"

EnemyStateHandler::EnemyStateHandler() {
	nextState = std::make_shared<IdleState>();
}

std::shared_ptr<EState> EnemyStateHandler::Update(Enemy& enemy)
{
	nextState = nextState->Update(enemy);
	return shared_from_this();
}

void EnemyStateHandler::Draw(Enemy& enemy)
{
	nextState->Draw(enemy);
}

