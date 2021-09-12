#pragma once

#include "../../Core/State.h"

class FBSpearAtk : public State{
public:
    FBSpearAtk();
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor &actor) override;
    ~FBSpearAtk() override;

protected:


private:
    int attackCounter = 120;
    Texture2D bossMap;
    int counter = 40;
    bool secondAttack = false;
};