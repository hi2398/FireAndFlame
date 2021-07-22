#pragma once

#include "../../Core/EState.h"

class AttackingState : public EState {
public:
    AttackingState(Enemy& enemy);
    std::shared_ptr <EState> Update(Enemy& enemy) override;
    void Draw(Enemy& enemy)override;

    ~AttackingState() = default;

protected:


private:
    int attackFrameCounter = 0;
    Rectangle attackHitbox = {};
};