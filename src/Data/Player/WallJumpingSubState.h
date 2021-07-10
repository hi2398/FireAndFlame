#pragma once

#include "../../Core/State.h"


class WallJumpingSubState : public State {
public:
    std::shared_ptr <State> Update(Actor& actor) override;
    void Draw(Actor& actor) override;

    ~WallJumpingSubState() override = default;

protected:


private:
    int wallJumpDirection;

};