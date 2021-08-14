#pragma once

#include "../../Core/EState.h"
#include "../../Core/Enemy.h"

class TBJumpUpStage : public EState {
public:
	TBJumpUpStage(Enemy& enemy);
	std::shared_ptr<EState> Update(Enemy& enemy) override;
	void Draw(Enemy& enemy) override;
	void PrepareJump(Enemy& enemy);
protected:

private:
	Vector2 reference{};
	Vector2 playerReference{};
	bool jumpSecondTime{ false };
};