#pragma once

#include "../../Core/State.h"

class FBIdleDown : public State {
public:
    FBIdleDown();
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor &actor) override;
    ~FBIdleDown() override;

protected:


private:
    Texture2D bossMap;
    int decideCounter = 260;
    int attackCounter = 250;
};
