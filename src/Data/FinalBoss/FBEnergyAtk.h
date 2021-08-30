#pragma once

#include "../../Core/State.h"


class FBEnergyAtk : public State {
public:
    FBEnergyAtk();
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor &actor) override;
    ~FBEnergyAtk() override = default;

protected:


private:
    int attackCounter = 200;
};