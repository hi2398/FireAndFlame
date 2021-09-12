#pragma once

#include "../../Core/State.h"

//enum class NextAction{None ,SpearAtk, SwordAtk, EnergyAtk, FlyDown};

class FBFlyDown : public State {
public:
    FBFlyDown();
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor &actor) override;
    ~FBFlyDown() override;

protected:

private:
    Texture2D bossMap;
    int counter = 40;
    int waitCounter = 60;
};
