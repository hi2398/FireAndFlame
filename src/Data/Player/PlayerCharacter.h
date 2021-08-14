#pragma once
#include "../../Core/Actor.h"
#include "raylib.h"
#include "../../Core/Observer/Observer.h"
#include "../../Core/State.h"



enum class ACTION {MELEE_ATTACK, RANGED_ATTACK, NONE};


class PlayerCharacter : public Actor {
public:
    PlayerCharacter();
    void Draw() override;
    void Update() override;
    ~PlayerCharacter() override = default;

    Observer& GetObserver() const;

    int GetHealth() const;
    void SetHealth(int health);
    const static int GetMaxHealth();

    ACTION GetNextAction();
    void SetNextAction(ACTION action);

    bool IsInvulnerable();
    void SetInvulnerable(bool invulnerable);

    bool disablePlayerMovement = false;
    void BlockPlayerControls(bool playerMovement);
    
    void SetPlayerDecreasingHealth(bool isDecreasing){
        isHealthDecreasing = isDecreasing;
    }

    bool ConrolsDisabled() const;

    void ChangeCameraControl();

    bool DashReady() const;
    void SetDashIsReady(bool ready);

	//2Dcam
	Camera2D camera = { 0 };
    bool followCam{ true };
    
    //cam hitbox
    Rectangle visibleScreen = {};

    //player hitbox
    Rectangle playerHitbox = { 0 };


    //draw player only in game scene
    bool active = true;

    //collision detection with scene objects
	bool isGrounded = false;

    //attack state and counter to reset attack pattern
	int resetAttack = 0;
	int attackState = 0;

    int GetFrame();
    int GetCurrentFrame();

    Texture2D upperBody;
    Texture2D lowerBody;
    Texture2D attackSprite;
    Texture2D spriteSheetMagmos;

protected:

private:
    const float playerWidth = 20.0f;
    const float playerHeight = 32.0f;
    static constexpr int max_health{100};
    int healthTimer{}; //decrease
    static constexpr int HEALTH_INTERVAL{30};
    static constexpr int DASH_COOLDOWN{ 60 };
    bool invulnerable{ false };
    bool isHealthDecreasing = true;
    int invulnerableCounter = 0;
    bool controlsBlocked = false;
    bool dashIsReady{ true };
    int dashCounter = 0;

    int playerFrameCounter = 0;
    int currentFrame = 0;

    bool invulnerableVisualized{ false };

   

    //attack
    ACTION nextAction{ACTION::NONE};

    std::shared_ptr<Observer> observer;
    std::shared_ptr<State> movementState;
    std::shared_ptr<State> actionState;
};


