#pragma once

#include "../../Core/State.h"

class FBSwordAtk : public State {
public:
    FBSwordAtk();
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor &actor) override;
    ~FBSwordAtk() override = default;

protected:


private:
    int decideCounter = 280;
};