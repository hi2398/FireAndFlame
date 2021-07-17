#pragma once

#include "../../Core/EState.h"

class EnemyStateHandler :  public EState{
public:

    EnemyStateHandler();

    std::shared_ptr<EState> Update(Enemy& enemy) override;
    void Draw(Enemy& enemy) override;

    ~EnemyStateHandler() override = default;

protected:


private:
    std::shared_ptr<EState> nextState;
};