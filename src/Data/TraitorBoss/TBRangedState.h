#pragma once

#include "../../Core/EState.h"
#include "../../Core/Enemy.h"

class TBRangedState : public EState {
public:
	TBRangedState(Enemy& enemy);
	std::shared_ptr<EState> Update(Enemy& enemy) override;
	void Draw(Enemy& enemy) override;
protected:

private:
	int stateExeCounter = 0;
};