#pragma once

#include "../../Core/EState.h"
#include "../../Core/Enemy.h"

class TBSeekCoal : public EState {
public:
	TBSeekCoal(Enemy& enemy);
	std::shared_ptr<EState> Update(Enemy& enemy) override;
	void Draw(Enemy& enemy) override;

	void CheckForCoal(Enemy& enemy);
protected:

private:
	bool noCoalFound{ false };
};