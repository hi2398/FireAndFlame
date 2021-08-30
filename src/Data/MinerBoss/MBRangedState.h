#pragma once

#include "../../Core/EState.h"
#include "MinerBoss.h"


class MBRangedState : public EState {
public:
    explicit MBRangedState(Enemy &enemy);
    std::shared_ptr<EState> Update(Enemy &enemy) override;
    void Draw(Enemy &actor) override;
    ~MBRangedState() override = default;

protected:


private:
    std::shared_ptr<EState> Attack(Enemy& enemy);
    std::shared_ptr<EState> Windup(Enemy& enemy);
    bool windup{true};
    bool playerHit{false};
    bool returning{false};
    const float startTimer{40};
    float timer{}; //set in ctor
    Vector2 currentAttackCenter{};
    Vector2 attackStart{};
    Vector2 attackEnd{};
    const int dmg{3};
    const float dmgRadius{16.f};
    const float reach{4.f*32.f};
    Rectangle textureRec{};
    Rectangle throwRec{};
    int currentAttackTimer{};
    const int attackTimer{45};



};


