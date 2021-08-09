#pragma once

#include "../../Core/Enemy.h"
#include "../../Core/EState.h"

class TraitorBoss : public Enemy {
public:
    explicit TraitorBoss(Vector2 location);
    void Draw() override;
    void Update() override;
    void ReceiveDamage(int damage) override;
    ~TraitorBoss() override = default;

protected:


private:
    const Vector2 levelExit{};

    std::shared_ptr<EState> activeState;
    void OnDeath();

    //handle traitor health
    int healthtimer = 0;
    static constexpr int HEALTH_INTERVAL{ 30 };
    static constexpr int MAX_HEALTH{ 100 };

    bool isFighting{ false };
};