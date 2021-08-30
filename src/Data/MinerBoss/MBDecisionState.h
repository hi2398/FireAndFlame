#pragma once

#include <iostream>
#include "../../Core/EState.h"

class MBDecisionState : public EState {
public:
    MBDecisionState(Enemy &enemy);
    std::shared_ptr <EState> Update(Enemy &actor) override;
    void Draw(Enemy &actor) override;
    ~MBDecisionState() override = default;

protected:


private:
    static std::shared_ptr<EState> DecideByChance(Enemy& enemy);
    int delay{60};

};


