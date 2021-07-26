#pragma once

#include "../../Core/PlayerStates.h"

class WallSlideSubState : public PlayerStates {
public:
    WallSlideSubState(Actor& player);
    std::shared_ptr <State> Update(Actor& player) override;
    void Draw(Actor& player) override;

    ~WallSlideSubState() override = default;

protected:


private:

};