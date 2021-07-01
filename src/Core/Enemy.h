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
    void SetHealth(int pHealth);
    bool CheckLineOfSight(Vector2 pOrtsVector, Vector2 pRichtungsVector, const std::unique_ptr<Tilemap>& tilemap);
    float GetDistance(Vector2 pVector1, Vector2 pVector2);
    bool CheckOnScreen();
    ~Enemy() override = default;

protected:
    bool MakeDecision(int pProbability);
    EnemyTypes aType;
    int aHealth{};
    bool aHasLineOfSight=0;
    int aState=0;
    Rectangle aHitbox{};
    Texture2D aTexture{};


    
private:

};


