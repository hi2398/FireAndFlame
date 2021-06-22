#pragma once

#include <memory>
#include "Actor.h"

class State : public std::enable_shared_from_this<State> {
public:

    virtual std::shared_ptr<State> Update(Actor &actor) = 0;
    virtual ~State() = default;
protected:

private:

};


