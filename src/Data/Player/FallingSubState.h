#pragma once

#include "../../Core/PlayerStates.h"

class FallingSubState : public PlayerStates {
public:
    FallingSubState(Actor& player);
    std::shared_ptr <State> Update(Actor& player) override;
    void Draw(Actor& player) override;

    ~FallingSubState() override = default;

protected:


private:
    float gravity = 1.0f;

};


