#pragma once

#include "../../Core/EState.h"

class IdleState : public EState {
public:
    IdleState(Enemy& enemy);
    std::shared_ptr <EState> Update(Enemy& enemy) override;
    void Draw(Enemy& enemy)override;

    ~IdleState() = default;

protected:


private:
    int idleFrameCounter = 0;
    Rectangle drawRec;
};