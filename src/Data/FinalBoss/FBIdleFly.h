#pragma once

#include "../../Core/State.h"

enum class NextAction{None ,SpearAtk, SwordAtk, EnergyAtk, FlyDown};

class FBIdleFly : public State {
public:
    FBIdleFly();
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor &actor) override;
    ~FBIdleFly() override = default;

protected:


private:
    NextAction nextAction{NextAction::None};
    int decideCounter = 200;
};
