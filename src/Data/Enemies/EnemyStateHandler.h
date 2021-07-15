#pragma once
#include "../../Core/Enemy.h"
#include "../../Core/State.h"

class EnemyStateHandler :  public State{
public:

    EnemyStateHandler();

    std::shared_ptr<State> Update(Actor& actor) override;
    void Draw(Actor& actor) override;

    ~EnemyStateHandler() override = default;

protected:


private:
    std::shared_ptr<State> nextState;
};