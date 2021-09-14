#pragma once

#include "../../Core/State.h"
class FBChangeStates : public State {
public:
    FBChangeStates();
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor &actor) override;
    ~FBChangeStates() override;

protected:


private:
    Texture2D bossMap;
    int counter = 260;
};
