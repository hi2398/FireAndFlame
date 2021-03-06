#pragma once

//created by Robin on 05.07.2021
#include "../../Core/Enemy.h"
#include "../../Core/EState.h"



class Howler : public Enemy
{
public:
	explicit Howler(Vector2 initialPos, EnemyLevel enemyLevel);
	void Update() override;
	void Draw() override;
	~Howler();
private:


	std::shared_ptr<EState> activeState;
};