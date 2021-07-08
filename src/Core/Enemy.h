#pragma once

//created by Robin on 29.06.2021
#include "Actor.h"
#include "EnemyTypes.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

enum class EnemyState {Idle, Roaming, Approaching, Fleeing, Stunned, Attacking, Seeking};

class Enemy : public Actor {
public:
    explicit Enemy(EnemyTypes enemyType);
    void Draw() override = 0;
    void Update() override = 0;
    [[nodiscard]] EnemyTypes GetEnemyType() const;
    void ReceiveDamage(int damage);
    bool CheckLineOfSight(Vector2 startLocation, Vector2 endLocation, const std::unique_ptr<Tilemap>& tilemap);
    float GetDistance(Vector2 startLocation, Vector2 endLocation);
    bool CheckOnScreen();
    ~Enemy() override = default;

protected:
    bool MakeDecision(int probability);
    EnemyTypes enemyType;
    int health{3};
    bool hasLineOfSight{false};
    bool IsAttacking;
    EnemyState state{EnemyState::Idle}; // 0=Idle, 1=Roaming, 2=Approaching, 3=fleeing, 4=Stunned, 5=attacking, 6=Seeking
    int stunCounter;
    const int stunDuration = 100;
    int attackCounter;
    const int attackDuration = 20;
    int seekingCounter;
    const int seekingDuration = 100;
    int idleWorkCounter;
    const int idleWorkDuration=100;
    Rectangle hitbox{};
    Rectangle attackArea{};
    Texture2D texture{};
    Vector2 lastSeen{};


    
private:

};


