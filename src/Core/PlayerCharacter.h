#pragma once
#include "Actor.h"
#include "raylib.h"

class PlayerCharacter : public Actor {
public:
    PlayerCharacter();
    void Draw() override;
    void Update() override;
    ~PlayerCharacter() override = default;

    void Jump();
    void RunJump();

    void Attack();
    void RunAttack();

    void Fireball();
    void RunFireball();

    void ChargingAttack();

    void ChargedAttack();
    void RunChargedAttack();

    void Move(int direction);

    int GetHealth() const;
    void SetHealth(int health);

    Vector2 GetPosition() const;
    Vector2 SetPosition(Vector2 newPosition);

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
    Vector2 vectorPlayer = { 0 };

    //jump&fall
    
    bool canDoubleJump = true;
    int jumpState = 0;
    float verticalSpeed = 3.0f;
    bool isJumping = false;
    bool isAirborne = false;
    float gravityMultiplier = 1.5f;

    //attack
    Vector2 vectorFireball = {0};
    Rectangle spearHitbox = {0,0,40,5};
    int spearRotation = 300;
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
};


