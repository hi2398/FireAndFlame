#pragma once

#include "../../Core/State.h"

enum class NextAction{None ,SpearAtk, SwordAtk, EnergyAtk, FlyDown};

class FBIdleFly : public State {
public:
    FBIdleFly();
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor &actor) override;
    ~FBIdleFly() override;

protected:


private:
    NextAction nextAction{NextAction::None};
    Texture2D bossMap;
    int counter = 40;
    int decideCounter = 200;
};
