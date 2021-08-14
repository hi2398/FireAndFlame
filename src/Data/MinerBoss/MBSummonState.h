#pragma once

#include "../../Core/EState.h"

enum class SummonSteps{MoveToSpot, JumpUp, Summon, ReturnToGround, Done};

class MBSummonState : public EState {
public:
    explicit MBSummonState(Enemy &enemy);
    std::shared_ptr<EState> Update(Enemy &enemy) override;
    void Draw(Enemy &actor) override;
    ~MBSummonState() override = default;

protected:


private:
    int summonTimer{45};
    SummonSteps summonStep{SummonSteps::MoveToSpot};
    const Vector2 jumpStart{57*32, 90*32};
    const Vector2 summonSpot{59*32, 87*32};

    float lerpAlpha{0};

    void MoveToSpot(Enemy& enemy);
    void JumpUp(Enemy& enemy);
    void Summon(Enemy& enemy);
    void ReturnToGround(Enemy& enemy);


    //spawn points for enemies
    const Vector2 spawn{58*32, 85*32};
    const Vector2 spawn2{46*32, 85*32};
};


