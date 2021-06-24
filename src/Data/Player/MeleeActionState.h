#pragma once

#include "../../Core/State.h"

class MeleeActionState : public State {
public:
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor& actor) override;

    ~MeleeActionState() override = default;

protected:


private:
    bool actionDone{false};

    //attack variables
    Rectangle spearHitbox = {0,0,40,5};
    bool isSwiping = false;
    int attackState = 0;
    float spearRotation = 300;
    int stabbingDistance = 0;
    int chargingCounter = 0;
    int resetAttack = 0;
};


