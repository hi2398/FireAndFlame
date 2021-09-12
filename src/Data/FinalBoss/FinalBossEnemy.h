#pragma once

#include "../../Core/Enemy.h"
#include "../../Core/State.h"
#include "BossSword.h"

class FinalBossEnemy : public Enemy{
public:
    FinalBossEnemy(Vector2 location);
    void Update() override;
    void Draw() override;
    void ChangeTargetPosition(Vector2 newPos);
    void ChangeSwordPosition(Vector2 newPos);
    void ReceiveDamage(int damage) override;
    Vector2 GetPositionFix();
    int GetHealth();
    ~FinalBossEnemy() override;
protected:


private:
    std::shared_ptr<BossSword> sword;
    int magnitude = 80;
    Vector2 bossPosition, moveTowardsPosition;
    Texture2D texture;
    std::shared_ptr<State> state;
    int swordCounter = 0;
};
