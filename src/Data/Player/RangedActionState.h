#pragma once

#include "../../Core/PlayerStates.h"

class RangedActionState : public PlayerStates {
public:
    RangedActionState(Actor& player);
    std::shared_ptr <State> Update(Actor& player) override;
    void Draw(Actor& player) override;

    ~RangedActionState() override = default;

protected:


private:
    bool actionDone{false};

    //fireball
    int fireballDirection;
    Vector2 vectorFireball = { 0 };
    bool isShootingFireball = false;
};


