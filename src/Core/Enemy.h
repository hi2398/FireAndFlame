#pragma once

//created by Robin on 29.06.2021
#include "Actor.h"
#include "EnemyTypes.h"
#include <iostream>
#include "../Global.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

class Enemy : public Actor {
public:
    Enemy();
    void Draw() override = 0;
    void Update() override = 0;
    [[nodiscard]] EnemyTypes GetEnemyType() const;
    void RecieveDamage(int pDamage);
    bool CheckLineOfSight(Vector2 pOrtsVector, Vector2 pRichtungsVector, const std::unique_ptr<Tilemap>& tilemap);
    float GetDistance(Vector2 pVector1, Vector2 pVector2);
    bool CheckOnScreen();
    ~Enemy() override = default;

protected:
    bool MakeDecision(int pProbability);
    EnemyTypes aType;
    int aHealth{};
    bool aHasLineOfSight=0;
    bool aIsattacking;
    int aState=0; // 0=Idle, 1=Roaming, 2=Approaching, 3=fleeing, 4=Stunned, 5=attacking, 6=Seeking
    int aStunCounter;
    const int aStunDuration = 100;
    int aAttackCounter;
    const int aAttackDuration = 300;
    int aSeekingcounter;
    const int aSeekingDuration = 1000;
    int aIdleWorkCounter;
    const int aIdleWorkDuration=500;
    Rectangle aHitbox{};
    Rectangle aAttackArea{};
    Texture2D aTexture{};
    Vector2 aLastSeen{};


    
private:

};


