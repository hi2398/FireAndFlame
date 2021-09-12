#pragma once

#include "../../Core/State.h"


class FBBossDying: public State {
public:
    FBBossDying();
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor &actor) override;
    ~FBBossDying() override;

protected:


private:
    Texture2D bossMap;
    int counter = 0;
};
