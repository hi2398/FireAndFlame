#pragma once

#include "../../Core/EState.h"

class AttackingState : public EState {
public:
    AttackingState(Enemy& enemy);
    std::shared_ptr <EState> Update(Enemy& enemy) override;
    void Draw(Enemy& enemy)override;

    ~AttackingState() = default;

protected:


private:
    int attackCounter = 0;
    Rectangle attackHitbox = {};

    //toastcat variables
    float toastSpeed = 15.0f;
    float toastDistance = 0.0f;
    float attackDirection = 1;
    float toastGravity = 1.0f;
    bool homingToast{ false };
    Texture2D toastTexture;
    Vector2 toastMissile{};
    Rectangle toastHitbox;

    float yDiff;
    float xDiff;

    //howler variables
    float movingDistance = 0;
};