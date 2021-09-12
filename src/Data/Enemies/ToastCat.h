#pragma once
#include "../../Core/Enemy.h"
#include "../../Core/EState.h"

class ToastCat : public Enemy
{
public:
	explicit ToastCat(Vector2 initalLoc);
	void Update() override;
	void Draw() override;
	~ToastCat();

private:
	std::shared_ptr<EState> activeState;
};

