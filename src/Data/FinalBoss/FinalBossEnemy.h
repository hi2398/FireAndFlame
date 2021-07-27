#pragma once

#include "../../Core/Enemy.h"
#include "../../Core/State.h"

class FinalBossEnemy : public Enemy{
public:
    FinalBossEnemy(Vector2 location);
    void Update() override;
    void Draw() override;
    void ChangeTargetPosition(Vector2 newPos);
    void ReceiveDamage(int damage) override;
    ~FinalBossEnemy() override = default;
protected:


private:
    int magnitude = 80;
    Vector2 bossPosition, moveTowardsPosition;
    Texture2D texture;
    std::shared_ptr<State> state;
};
