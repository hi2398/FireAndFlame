#pragma once

#include "../../Core/Enemy.h"
#include "../../Core/EState.h"



class SpiderBot : public Enemy
{
public:
	explicit SpiderBot(Vector2 initialPos, EnemyLevel enemyLevel);
	void Update() override;
	void Draw() override;
	~SpiderBot();

	

private:
	void CheckEdgeColl();

	std::shared_ptr<EState> activeState;
};