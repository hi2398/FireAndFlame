#pragma once

#include "../../Core/State.h"
class FBSpawnEDown : public State{
public:
    FBSpawnEDown();
    std::shared_ptr <State> Update(Actor &actor) override;
    void Draw(Actor &actor) override;
    ~FBSpawnEDown() override = default;

protected:


private:
    int waitCounter = 180;
};