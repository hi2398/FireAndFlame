#pragma once

#include "../../Core/Enemy.h"
#include "../../Core/State.h"

enum class MinerBossPhase{First, Second};

class MinerBoss : public Enemy {
public:
    explicit MinerBoss(Vector2 location);
    void Draw() override;
    void Update() override;
    void ReceiveDamage(int damage) override;
    ~MinerBoss() override = default;

protected:


private:
    const Vector2 levelExit{58*32-96, 29*32-96};

    std::shared_ptr<State> state;
    void OnDeath();
    MinerBossPhase bossPhase{MinerBossPhase::First};
};


