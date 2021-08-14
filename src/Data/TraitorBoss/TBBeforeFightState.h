#pragma once

#include "../../Core/EState.h"
#include "../../Core/Enemy.h"

class TBBeforeFightState : public EState {
public:
	TBBeforeFightState(Enemy& enemy);
	std::shared_ptr<EState> Update(Enemy& enemy) override;
	void Draw(Enemy& enemy) override;
protected:

private:
	Texture2D pseudoTexture{};

	int textCounter = 0;
};