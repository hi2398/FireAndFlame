#pragma once

#include "../../Core/EState.h"

class ApproachingState : public EState {
public:
    ApproachingState(Enemy& enemy);
    std::shared_ptr <EState> Update(Enemy& enemy) override;
    void Draw(Enemy& enemy)override;

    ~ApproachingState() = default;

protected:


private:
    int aggroCooldown = 0;
    int approachingFrameCounter = 0;
    Rectangle drawRec;
    float movingDistance = 0;
    Vector2 movingToPlayer;

    int collCheckLeft = 0;
    int collCheckRight = 0;


    Rectangle edgeSeekerLeft{};
    Rectangle edgeSeekerRight{};
    Rectangle tileRec{ 0,0,32,32 };
   
};