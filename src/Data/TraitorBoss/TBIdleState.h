#pragma once

#include "../../Core/EState.h"
#include "../../Core/Enemy.h"

class TBIdleState : public EState {
public:
	TBIdleState(Enemy& enemy);
	std::shared_ptr<EState> Update(Enemy& enemy) override;
	void Draw(Enemy& enemy) override;
	void CheckForCoal(Enemy& enemy);
protected:

private:
	bool noCoalFound{ true };
	int decisionCounter = 0;
};