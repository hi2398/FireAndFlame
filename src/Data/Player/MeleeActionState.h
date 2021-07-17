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
    Rectangle spearHitbox = {0,0,40,6};
    float spearRotation;
    int stabbingDistance = 0;
    int chargingCounter = 0;
    int resetAttack = 0;
    Rectangle collisionRec;
};


