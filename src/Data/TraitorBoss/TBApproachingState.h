#pragma once

#include "../../Core/EState.h"

class TBApproachingState : public  EState {

public:
	TBApproachingState(Enemy& enemy);
	std::shared_ptr<EState> Update(Enemy& enemy) override;
	void Draw(Enemy& enemy) override;
protected:

private:
	Vector2 playerReference{};
	int approachingCounter = 0;
};