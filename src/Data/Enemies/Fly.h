#pragma once

#include "../../Core/Enemy.h"
#include "../../Core/EState.h"



class Fly : public Enemy
{
public:
	explicit Fly(Vector2 initialPos);
	void Update() override;
	void Draw() override;
	~Fly() = default;
private:


	std::shared_ptr<EState> activeState;
};