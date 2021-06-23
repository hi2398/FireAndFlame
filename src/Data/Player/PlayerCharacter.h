#pragma once
#include "../../Core/Actor.h"
#include "raylib.h"
#include "../../Core/Observer/Observer.h"
#include "../../Core/State.h"
#include "MovementState.h"
#include <iostream>


enum class ACTION {MELEE_ATTACK, RANGED_ATTACK, NONE};

class PlayerCharacter : public Actor {
public:
    PlayerCharacter();
    void Draw() override;
    void Update() override;
    ~PlayerCharacter() override = default;

    Observer& GetObserver() const;

    void Attack();
    void RunAttack();

    void Fireball();
    void RunFireball();

    void ChargingAttack();

    void ChargedAttack();
    void RunChargedAttack();


    int GetHealth() const;
    void SetHealth(int health);

    ACTION GetNextAction();
    void SetNextAction(ACTION action);

	//2Dcam
	Camera2D camera = { 0 };

    //public player variable
    Rectangle playerHitbox = { 0 };

    //draw player only in game scene
    bool visible = true;

    //collision detection with scene objects
	bool isGrounded = false;
protected:

private:


    int health{100};
    //player
    Texture2D texturePlayer;

    //attack
    ACTION nextAction{ACTION::NONE};


    Vector2 vectorFireball = {0};
    Rectangle spearHitbox = {0,0,40,5};
    float spearRotation = 300;
    int stabbingDistance = 0;
    bool isSwiping = false;
    bool isCharged = false;
    int chargingCounter = 0;
    bool isShootingFireball = false;
    int resetAttack  = 0;
    int attackState = 0;

    //bool for input functions
    bool attackCommand = false;
    bool chargedAttackCommand = false;
    bool fireballCommand = false;

    std::shared_ptr<Observer> observer;
    std::shared_ptr<State> movementState;
    std::shared_ptr<State> actionState;
};


