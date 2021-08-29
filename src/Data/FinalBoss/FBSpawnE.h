#pragma once

#include "../../Core/State.h"

class FBSpawnE : public State{
public:
    FBSpawnE();
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor &actor) override;
    ~FBSpawnE() override = default;

private:
    int waitCounter = 180;
protected:
    Sound bossSpeech;
};
