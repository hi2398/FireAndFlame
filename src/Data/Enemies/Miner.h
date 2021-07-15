#pragma once

//created by Robin on 05.07.2021
#include "../../Core/Enemy.h"
#include "../../Core/State.h"



class Miner : public Enemy
{
public:
	explicit Miner(Vector2 initialPos);
	void Update() override;
	void Draw() override;
	~Miner();
private:
	bool aOnScreen;
	Vector2 aEdgeSeekerRight;
	Vector2 aEdgeSeekerLeft;
	Vector2 aWallSeekerRight;
	Vector2 aWallSeekerLeft;
	int aDamageOutput = 3;
	int aMovementSpeed = 1;
	void Move(Direction pDirection);

	std::shared_ptr<State> activeState;
};