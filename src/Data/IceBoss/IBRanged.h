#pragma once

#include "../../Core/State.h"

class IBRanged : public State{
public:
    IBRanged();

    std::shared_ptr <State> Update(Actor &actor) override;

    void Draw(Actor &actor) override;

    ~IBRanged() override = default;

protected:


private:


};


