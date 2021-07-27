#pragma once

//created by Robin on 05.07.2021
#include "../../Core/Enemy.h"
#include "../../Core/EState.h"



class Miner : public Enemy
{
public:
	explicit Miner(Vector2 initialPos);
	void Update() override;
	void Draw() override;
	~Miner() = default;
private:
	

	std::shared_ptr<EState> activeState;
};