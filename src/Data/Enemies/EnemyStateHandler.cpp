#include "EnemyStateHandler.h"
#include <iostream>
#include "ApproachingState.h"
#include "AttackingState.h"
#include "RoamingState.h"
#include "IdleState.h"

EnemyStateHandler::EnemyStateHandler() {
	nextState = std::make_shared<IdleState>();
}

std::shared_ptr<State> EnemyStateHandler::Update(Actor& actor)
{
	auto enemy = static_cast<Enemy&>(actor);
	nextState = nextState->Update(enemy);
	return shared_from_this();
}

void EnemyStateHandler::Draw(Actor& actor)
{
	auto enemy = static_cast<Enemy&>(actor);
	nextState->Draw(enemy);
}

