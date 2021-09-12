#pragma once

#include "../../Core/Enemy.h"
#include "../../Core/EState.h"



class Saugi : public Enemy
{
public:
	explicit Saugi(Vector2 initialPos);
	void Update() override;
	void Draw() override;
	~Saugi();
private:


	std::shared_ptr<EState> activeState;
};