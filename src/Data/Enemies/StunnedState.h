#pragma once

#include "../../Core/EState.h"
#include "../HeartObject.h"

class StunnedState : public EState {
public:
    StunnedState(Enemy& enemy);
    std::shared_ptr <EState> Update(Enemy& enemy) override;
    void Draw(Enemy& enemy)override;

    ~StunnedState() = default;

protected:


private:
    int stunnedFrameCounter = 0;
    int stunnedOffset = 0;
    Rectangle enemySight{ 0 };
    int spiderBotRotation = 0;

    std::unique_ptr<HeartObject> heart;
};