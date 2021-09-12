#pragma once

#include "../../Core/State.h"


class FBEnergyAtk : public State {
public:
    FBEnergyAtk();
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor &actor) override;
    ~FBEnergyAtk() override;

protected:


private:
    int attackCounter = 200;
    Texture2D bossMap;
    int counter = 40;
};