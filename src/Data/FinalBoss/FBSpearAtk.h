#pragma once

#include "../../Core/State.h"

class FBSpearAtk : public State{
public:
    FBSpearAtk();
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor &actor) override;
    ~FBSpearAtk() override = default;

protected:


private:
    int attackCounter = 120;
    bool secondAttack = false;
};