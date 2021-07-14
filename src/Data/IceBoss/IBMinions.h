#pragma once

#include "../../Core/State.h"

class IBMinions : public State {
public:
    IBMinions();
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor &actor) override;
    ~IBMinions() override = default;

protected:


private:


};
