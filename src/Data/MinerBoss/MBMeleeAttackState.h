#pragma once

#include "../../Core/EState.h"

class MBMeleeAttackState : public EState {
public:
    MBMeleeAttackState(Enemy &enemy);
    std::shared_ptr<EState> Update(Enemy &actor) override;
    void Draw(Enemy &actor) override;
    ~MBMeleeAttackState() override = default;

protected:


private:



};


