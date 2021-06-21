#pragma once

#include <memory>
#include "Actor.h"

class State {
public:

    virtual std::unique_ptr <State> Update(Actor &actor) = 0;
    virtual ~State() = default;
protected:

private:

};


