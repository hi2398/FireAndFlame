    #pragma once
#include "../../Core/Actor.h"
#include "raylib.h"
#include "../../Core/Observer/Observer.h"
#include "../../Core/State.h"



enum class ACTION {MELEE_ATTACK, RANGED_ATTACK, NONE};
enum class AbilitiesUnlocked {None = 0, Dash = 1, Walljump = 2 , Doublejump = 3};


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

    bool IsInvulnerable() const;
    void SetInvulnerable(bool invulnerable);

    bool disablePlayerMovement = false;
    void BlockPlayerControls(bool playerMovement);
    
    void SetPlayerDecreasingHealth(bool isDecreasing){
        isHealthDecreasing = isDecreasing;
    }

    bool InputDisabled() const;

    void ChangeCameraControl();

    bool DashReady() const;
    void SetDashIsReady(bool ready);

    bool GetLastTickGroundedState() const;

    bool IsDashUnlocked() const;
    void SetDashUnlocked(bool dashUnlocked);

    bool IsWalljumpUnlocked() const;
    void SetWallJumpUnlocked(bool wjUnlocked);

    bool CanMove() const;
    void SetCanMove(bool canMove);

    void HoldInPlace(bool hold, Vector2 thisPos);
    bool IsHoldInPlace()const;

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

    int GetFrame() const;
    int GetCurrentFrame() const;

    Texture2D upperBody;
    Texture2D lowerBody;
    Texture2D attackSprite;
    Texture2D spriteSheetMagmos;

    AbilitiesUnlocked GetUnlockedAbilities() const;
    void SetUnlockedAbilityLevel(AbilitiesUnlocked abilitiesUnlocked);

protected:

private:
    void CheckUnlockedAbilities();
    AbilitiesUnlocked abilitiesUnlocked{AbilitiesUnlocked::None};
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
    bool groundedLastFrame{ true };
   
    bool dashUnlocked{ false };
    bool wjUnlocked{false};

    bool canMove{true};
    bool isHoldInPlace{ false };

    Vector2 holdThisPosition{};

    //attack
    ACTION nextAction{ACTION::NONE};

    std::shared_ptr<Observer> observer;
    std::shared_ptr<State> movementState;
    std::shared_ptr<State> actionState;
};


