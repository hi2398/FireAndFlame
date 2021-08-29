#pragma once

#include "../../Core/EState.h"

class MBMeleeAttackState : public EState {
public:
    MBMeleeAttackState(Enemy &enemy);
    std::shared_ptr<EState> Update(Enemy &enemy) override;
    void Draw(Enemy &actor) override;
    ~MBMeleeAttackState() override = default;

protected:


private:
    std::shared_ptr<EState> Approach(Enemy& enemy);
    std::shared_ptr<EState> Attack(Enemy& enemy);

    bool inReach{false};
    Rectangle textureRec;
    int timer{30};
    int meleeDamage{5};
    float dmgRadius{16.f};
    bool playerHit{false};

};


