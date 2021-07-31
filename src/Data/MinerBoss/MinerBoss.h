#pragma once

#include "../../Core/Enemy.h"
#include "../../Core/State.h"

class MinerBoss : public Enemy {
public:
    explicit MinerBoss(Vector2 location);
    void Draw() override;
    void Update() override;
    void ReceiveDamage(int damage) override;
    ~MinerBoss() override = default;

protected:


private:
    const Vector2 levelExit{58*32, 29*32};

    std::shared_ptr<State> state;
    void OnDeath();
};


