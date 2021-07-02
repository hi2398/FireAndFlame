#pragma once

#include "../../Core/State.h"

class WallSlideSubState : public State {
public:
    std::shared_ptr <State> Update(Actor& actor) override;
    void Draw(Actor& actor) override;

    ~WallSlideSubState() override = default;

protected:


private:


};