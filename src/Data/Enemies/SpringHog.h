#pragma once

#include "../../Core/Enemy.h"
#include "../../Core/EState.h"



class SpringHog : public Enemy
{
public:
	explicit SpringHog(Vector2 initialPos, EnemyLevel enemyLevel);
	void Update() override;
	void Draw() override;
	~SpringHog();



private:

	std::shared_ptr<EState> activeState;
};