#pragma once

//created by Robin on 05.07.2021
#include "../../Core/Enemy.h"
#include "../../Core/EState.h"



class Howler : public Enemy
{
public:
	explicit Howler(Vector2 initialPos);
	void Update() override;
	void Draw() override;
	~Howler() = default;
private:


	std::shared_ptr<EState> activeState;
};