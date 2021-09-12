#pragma once

#include "../../Core/State.h"

class FBBigSpearAtk : public State{
public:
    FBBigSpearAtk();
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor &actor) override;
    ~FBBigSpearAtk() override;

protected:


private:
    Texture2D bossMap;
    int attackCounter = 120;
    bool secondAttack = false;
};