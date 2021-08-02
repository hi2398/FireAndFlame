#pragma once

//created by Robin on 29.06.2021
#include "Actor.h"


enum class EnemyState {Idle, Roaming, Approaching, Fleeing, Stunned, Attacking, Seeking};
enum class EnemyTypes { ToastCat, Miner, SpiderBot, Flyer, SpringHog, Howler, Saugi, Boss};
enum class EnemyLevel {Low, Medium, High};


class Enemy : public Actor {
public:
    void Draw() override {};
    void Update() override {};
    [[nodiscard]] EnemyTypes GetEnemyType() const;
    virtual void ReceiveDamage(int damage);

    void UpdateCollider(float xOffset, float yOffset, float width, float height);
    Rectangle GetCollider() const;

    ~Enemy() override = default;

    EnemyState GetEnemyState();
    void SetEnemyState(EnemyState state);

    float GetEnemyMovementSpeed();

    Texture2D GetTexture();

    void UpdateAttackHitbox();
    Rectangle GetAttackHitbox();

    bool IsInvulnerable();
    void SetInvulnerable(bool invulnerable);

    int GetDamageValue();

    EnemyLevel GetEnemyLevel() const;

    

protected:
    static float GetDistance(Vector2 startLocation, Vector2 endLocation);
    explicit Enemy(EnemyTypes enemyType);
    bool CheckOnScreen();
    bool MakeDecision(int probability);
    EnemyTypes enemyType;
    EnemyLevel enemyLevel;
    int health{3};
    bool hasLineOfSight{false};
    bool isAttacking;
    EnemyState state{EnemyState::Idle};
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
    float movementSpeed{ 1.0f };
    Rectangle attackHitbox = {};
    bool invulnerable{ false };
    int invulnerableCounter = 0;
    int damageValue = 5;

    
private:

};


