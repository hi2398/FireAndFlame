#pragma once

#include "../../Core/State.h"

class FallingSubState : public State {
public:
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor& actor) override;

    ~FallingSubState() override = default;

protected:


private:
    float gravity = 1.0f;
    


};


