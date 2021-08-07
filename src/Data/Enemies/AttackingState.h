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
    float attackDirection{};

    //toastcat variables
    Vector2 missile{};
    float yDiff;
    float xDiff;
    Vector2 toastInit{};

    //flyer variables
    Vector2 playerReference{};
    Vector2 shootToPlayer{};
    Vector2 foamInit{};

    //howler variables
    float movingDistance = 0;

    //spiderbot vartiable
    float spiderBotRotation = 0;

    //springhog variables
    float jumpDistance = 0.0f;
    int groundedCounter = 0;
};