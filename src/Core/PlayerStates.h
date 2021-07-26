#pragma once

#include <memory>
#include "State.h"


class PlayerStates : public State {
public:
    PlayerStates(Actor& player);
    [[nodiscard]] virtual std::shared_ptr<State> Update(Actor& player) = 0;
    virtual void Draw(Actor& player) = 0;
    virtual ~PlayerStates() = default;
protected:
    Rectangle activeFrame{};
    int stateFrameCounter = 0;
    int thisFrame = 0;
private:

};


