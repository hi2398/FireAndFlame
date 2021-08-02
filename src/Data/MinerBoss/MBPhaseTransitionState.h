#pragma once

#include "../../Core/State.h"

class MBPhaseTransitionState : public State {
public:
    MBPhaseTransitionState();
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor &actor) override;
    ~MBPhaseTransitionState() override = default;

protected:


private:


};


