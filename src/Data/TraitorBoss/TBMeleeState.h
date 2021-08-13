#pragma once

#include "../../Core/EState.h"
#include "../../Core/Enemy.h"

class TBMeleeState : public EState {
public:
	TBMeleeState(Enemy& enemy);
	std::shared_ptr<EState> Update(Enemy& enemy) override;
	void Draw(Enemy& enemy) override;
protected:

private:
	int randomAttack;
	int attackCounter = 0;
	Rectangle collisionRec{};
};