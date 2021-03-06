#pragma once

#include "../../Core/Enemy.h"
#include "../../Core/EState.h"



class Fly : public Enemy
{
public:
	explicit Fly(Vector2 initialPos, EnemyLevel enemyLevel);
	void Update() override;
	void Draw() override;
	~Fly();
private:


	std::shared_ptr<EState> activeState;
};