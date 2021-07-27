#pragma once

#include "../../Core/State.h"

enum class NextAction{None ,SpearAtk, SwordAtk, EnergyAtk, FlyDown};

class FBSpawnE : public State{
public:
    FBSpawnE();
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor &actor) override;
    ~FBSpawnE() override = default;

private:
protected:
};
