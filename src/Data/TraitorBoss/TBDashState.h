#pragma once

#include "../../Core/EState.h"
#include "../../Core/Enemy.h"

class TBDashState : public EState {
public:
	TBDashState(Enemy& enemy);
	std::shared_ptr<EState> Update(Enemy& enemy) override;
	void Draw(Enemy& enemy) override;
protected:

private:

};