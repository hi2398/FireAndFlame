#pragma once

#include "../HeartObject.h"
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


    int collCheckLeft = 0;
    int collCheckRight = 0;

    int flyApproachingCounter = 0;

    //SpiderBot variables
    float spiderBotRotation = 0;
    float approachingSpeed = 0;



    Rectangle edgeSeekerLeft{};
    Rectangle edgeSeekerRight{};
    Rectangle tileRec{ 0,0,32,32 };
    Vector2 playerReference{};
    Vector2 movingToPlayer{};

    std::unique_ptr<HeartObject> heart;
};