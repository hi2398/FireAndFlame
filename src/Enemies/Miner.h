#pragma once

//created by Robin on 05.07.2021
#include "../Core/Enemy.h"

class Miner : public Enemy
{
public:
	Miner(float pStartX, float pStartY);
	void Update() override;
	void Draw() override;
	~Miner();
private:
	bool aOnScreen;
	Vector2 aEdgeSeekerRight;
	Vector2 aEdgeSeekerLeft;
	int aDamageOutput = 3;
	int aMovementSpeed = 3;
	void Move(Direction pDirection);

};