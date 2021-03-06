#pragma once

#include "../../Core/Enemy.h"
#include "../../Core/EState.h"

class TraitorBoss : public Enemy {
public:
    explicit TraitorBoss(Vector2 location);
    void Draw() override;
    void Update() override;
    void ReceiveDamage(int damage) override;
    ~TraitorBoss() override;

protected:


private:
    void OnDeath();
    std::shared_ptr<EState> activeState;
    //handle traitor health
    int healthtimer = 0;
    static constexpr int HEALTH_INTERVAL{ 30 };
    static constexpr int MAX_HEALTH{ 100 };

    bool isFighting{ false };
    bool fightStarted{ false };

    int cooldown = 240;
};