#pragma once

#include "../../Core/State.h"

class FBSpawnE : public State{
public:
    FBSpawnE();
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor &actor) override;
    ~FBSpawnE() override;

private:
    int waitCounter = 180;
    Texture2D bossMap;
    int counter = 40;
protected:
};
