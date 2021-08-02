#pragma once
#include <vector>
#include "Object.h"
#include "raylib.h"
#include "Tilemap.h"

enum Direction{LEFT=-1, RIGHT=1};
enum class MOVEMENT { MOVE_LEFT, MOVE_RIGHT, IDLE, DASH_LEFT, DASH_RIGHT };
enum AttackDirection{ATT_LEFT = -1, ATT_RIGHT = 1};

class Actor : public Object {
public:
    explicit Actor(ObjectTypes type);
    void Update() override = 0;
    void Draw() override = 0;
    ~Actor() override=default;

    void SetLastPosition(Vector2 lastPos);
    Vector2 GetLastPosition();
    Direction GetDirection() const;
    void SetDirection(Direction direction);
    float GetGravityMultiplier() const;
    void SetGrounded(bool grounded);
    bool IsGrounded() const;
    void SetJumpCommand(bool jumpUp);
    bool GetJumpCommand() const;

    MOVEMENT GetNextMovement();
    void SetNextMovement(MOVEMENT movement);

    bool GetWallCollisionLeft() const;
    void SetWallCollisionLeft(bool hugWallLeft);

    bool GetWallCollisionRight() const;
    void SetWallCollisionRight(bool hugWallRight);

    bool GetHeadCollision() const;
    void SetHeadCollision(bool headCollision);

    float GetJumpSpeed() const;
    void SetJumpSpeed(float jumpSpeed);

    float GetFallingSpeed() const;
    void SetFallingSpeed(float fallingSpeed);

    int GetTimesJumped() const;
    void SetTimesJumped(int timesJumped);

    bool GetCanDoubleJump() const;
    void SetCanDoubleJump(bool canDoubleJump);

    bool GetIsRunning() const;
    void SetIsRunning(bool isRunning);

    bool GetWallJumpCommand() const;
    void SetWallJumpCommand(bool jumpOffWall);

    bool GetJumpBlocked() const;
    void SetJumpBlocked(bool jumpBlocked);

    int GetWallCounter() const;
    void SetWallCounter(int wallCounter);

    bool GetIsDashing() const;
    void SetIsDashing(bool isDashing);
    Vector2 Dash(int direction);

    bool GetCanDash() const;
    void SetCanDash(bool canDash);

    AttackDirection GetAttackDirection() const;
    void SetAttackDirection(Direction direction);

    bool GetIsSwiping() const;
    void SetIsSwiping(bool isSwiping);

    bool GetActionBlocked() const;
    void SetActionBlocked(bool actionBlocked);

    void LookAtPlayer(); //change direction to look at player

    void DrawDirectional(Vector2 location, Texture2D texture, Rectangle sourceRec = {0, 0, 32, 32}) const;

    int GetHealth() const;
    void SetHealth(int health);

protected:
    int health = 3;
    Vector2 lastTickPos;
    Direction direction{RIGHT};
    bool grounded{false};
    float gravityMultiplier = 1.0f;
    bool jumpUp = false;
    bool hugWallLeft{ false };
    bool hugWallRight{ false };
    bool headCollision{ false };
    float fallingSpeed = 0.0f;
    float jumpSpeed = 5.0f;
    bool canDoubleJump{ false };
    int timesJumped = 0;
    bool isRunning{false};
    bool jumpOffWall{ false };
    bool jumpBlocked{false};
    int wallCounter{0};
    float dashDistance = 96.0f;
    int dashCounter = 0;
    bool isDashing{ false };
    bool canDash{ true };
    AttackDirection attackDirection{ ATT_RIGHT };
    bool isSwiping{ false };
    bool actionBlocked{ false };


	//Movement
	MOVEMENT nextMovement{ MOVEMENT::IDLE };

    void CollisionGround(const std::unique_ptr<Tilemap>& tilemap);
    void CollisionLeft(const std::unique_ptr<Tilemap>& tilemap);
    void CollisionRight(const std::unique_ptr<Tilemap>& tilemap);
    void CollisionHead(const std::unique_ptr<Tilemap>& tilemap);


private:
    
    
};


