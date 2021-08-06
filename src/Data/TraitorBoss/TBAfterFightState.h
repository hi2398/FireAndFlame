#pragma once

#include "../../Core/EState.h"

class TBAfterFightState : public  EState {

public:
	TBAfterFightState(Enemy& enemy);
	std::shared_ptr<EState> Update(Enemy& enemy) override;
	void Draw(Enemy& enemy) override;
protected:

private:

};