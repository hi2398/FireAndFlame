#pragma once

#include "../../Core/State.h"

class IBSeek : public State {
public:
    IBSeek();
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor &actor) override;
    ~IBSeek() override = default;

protected:


private:

};


