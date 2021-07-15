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


	//2Dcam
	Camera2D camera = { 0 };
    //cam hitbox
    Rectangle visibleScreen = {};

    //player hitbox
    Rectangle playerHitbox = { 0 };


    //draw player only in game scene
    bool visible = true;

    //collision detection with scene objects
	bool isGrounded = false;

    //attack state and counter to reset attack pattern
	int resetAttack = 0;
	int attackState = 0;

    Texture2D texturePlayer;
    Texture2D textureWallSlide;

protected:

private:
    const float playerWidth = 20.0f;
    const float playerHeight = 32.0f;
    static constexpr int max_health{100};
    int health{max_health};
    int healthTimer{}; //decrease
    static constexpr int HEALTH_INTERVAL{30};

    //attack
    ACTION nextAction{ACTION::NONE};

    std::shared_ptr<Observer> observer;
    std::shared_ptr<State> movementState;
    std::shared_ptr<State> actionState;
};


