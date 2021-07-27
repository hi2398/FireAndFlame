#pragma once

#include "../../Core/State.h"

//enum class NextAction{None ,SpearAtk, SwordAtk, EnergyAtk, FlyDown};

class FBSwordAtk : public State {
public:
    FBSwordAtk();
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor &actor) override;
    ~FBSwordAtk() override = default;

protected:


private:
    //NextAction nextAction{NextAction::None};
    int decideCounter = 200;
};