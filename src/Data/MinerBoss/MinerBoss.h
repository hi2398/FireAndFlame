#pragma once

#include "../../Core/Enemy.h"
#include "../../Core/EState.h"

enum class MinerBossPhase{First, Transition, Second};

class MinerBoss : public Enemy {
public:
    explicit MinerBoss(Vector2 location);
    void Draw() override;
    void Update() override;
    void ReceiveDamage(int damage) override;
    ~MinerBoss() override = default;

    [[nodiscard]] int GetMaxHealth() const;
    [[nodiscard]] MinerBossPhase GetMinerBossPhase() const;
    void SetMinerBossPhase(MinerBossPhase bossPhase);
    void EnableDebris();

protected:


private:
    const Vector2 levelExit{58*32-96, 29*32-96};
    const int maxHealth{40};
    std::shared_ptr<EState> state;
    void OnDeath();
    MinerBossPhase bossPhase{MinerBossPhase::First};

    //falling debris
    bool enableDebris{false};
    Texture2D debrisTexture;
    int debrisTimer{100};
    const Vector2 debrisStartLoc{57*32, 80*32};
    const Vector2 debrisEndLoc{57*32, 90*32};
    Vector2 debrisDrawLoc{};
};


