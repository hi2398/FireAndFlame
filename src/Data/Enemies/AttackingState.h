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
    Texture2D missileTexture;
    Vector2 missile{};
    Rectangle missileHitbox;
    float yDiff;
    float xDiff;

    //flyer variables
    float missileSpeed = 5.0f;
    Vector2 playerReference{};
    Vector2 shootToPlayer{};

    //howler variables
    float movingDistance = 0;

    //spiderbot vartiable
    float spiderBotRotation = 0;

    //springhog variables
    float jumpDistance = 0.0f;
    int groundedCounter = 0;
};