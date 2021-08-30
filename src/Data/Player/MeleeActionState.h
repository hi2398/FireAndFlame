#pragma once
#include "../HitMarker.h"
#include "../Coal.h"
#include "../../Core/PlayerStates.h"

class MeleeActionState : public PlayerStates {
public:
    MeleeActionState(Actor&player);
    std::shared_ptr <State> Update(Actor& player) override;
    void Draw(Actor& player) override;

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


