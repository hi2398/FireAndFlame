#pragma once

#include <memory>
#include "Actor.h"


class State : public std::enable_shared_from_this<State> {
public:
    [[nodiscard]] virtual std::shared_ptr<State> Update(Actor& actor) = 0;
    virtual void Draw(Actor& actor) = 0;
    virtual ~State() = default;
protected:
    Rectangle activeFrame{};
    int stateFrameCounter = 0;
    int thisFrame = 0;
private:

};


