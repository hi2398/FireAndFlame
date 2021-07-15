#pragma once

//created by Robin on 29.06.2021
#include "Actor.h"


enum class EnemyState {Idle, Roaming, Approaching, Fleeing, Stunned, Attacking, Seeking};
enum class EnemyTypes { ToastCat, Miner, WatchBot, Flyer, SpringHog, Howler, Saugi, Boss};

class Enemy : public Actor {
public:

    void EnemyDefaultIdle();
    void Draw() override {};
    void Update() override {};
    [[nodiscard]] EnemyTypes GetEnemyType() const;
    virtual void ReceiveDamage(int damage);
    Rectangle GetCollider() const;
    ~Enemy() override = default;

    EnemyState GetEnemyState();
    void SetEnemyState(EnemyState state);

    Texture2D GetTexture();

protected:
    static bool CheckLineOfSight(Vector2 startLocation, Vector2 endLocation, const std::unique_ptr<Tilemap>& tilemap);
    static float GetDistance(Vector2 startLocation, Vector2 endLocation);
    explicit Enemy(EnemyTypes enemyType);
    bool CheckOnScreen();
    bool MakeDecision(int probability);
    EnemyTypes enemyType;
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

    int idleFrameCounter = 0;
    
private:

};


