#pragma once
#include <vector>
#include "Object.h"
#include "Component.h"
#include "raylib.h"
#include "Tilemap.h"

enum Direction{LEFT=-1, RIGHT=1};
enum class MOVEMENT { MOVE_LEFT, MOVE_RIGHT, IDLE, DASH_LEFT, DASH_RIGHT };

class Actor : public Object {
public:
    explicit Actor(ObjectTypes type);
    void Update() override = 0;
    void Draw() override = 0;
    ~Actor() override=default;

    void SetLastPosition(Vector2 lastPos);
    Vector2 GetLastPosition();
    Direction GetDirection() const;
    float GetGravityMultiplier();
    void SetGrounded(bool grounded);
    bool IsGrounded();
    void SetJumpCommand(bool jumpUp);
    bool GetJumpCommand();

    MOVEMENT GetNextMovement();
    void SetNextMovement(MOVEMENT movement);

    bool GetWallCollisionLeft();
    void SetWallCollisionLeft(bool hugWallLeft);

    bool GetWallCollisionRight();
    void SetWallCollisionRight(bool hugWallRight);

    bool GetHeadCollision();
    void SetHeadCollision(bool headCollision);

    float GetJumpSpeed();
    void SetJumpSpeed(float jumpSpeed);

    float GetFallingSpeed();
    void SetFallingSpeed(float fallingSpeed);

    int GetTimesJumped();
    void SetTimesJumped(int timesJumped);

    bool GetCanDoubleJump();
    void SetCanDoubleJump(bool canDoubleJump);

    bool GetIsRunning();
    void SetIsRunning(bool isRunning);

    bool GetWallJumpCommand();
    void SetWallJumpCommand(bool jumpOffWall);

    bool GetJumpBlocked();
    void SetJumpBlocked(bool jumpBlocked);

    int GetWallCounter();
    void SetWallCounter(int wallCounter);

    bool GetIsDashing();
    void SetIsDashing(bool isDashing);
    Vector2 Dash(int direction);

protected:
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

    void CollisionGround(const std::unique_ptr<Tilemap>& tilemap);
    void CollisionLeft(const std::unique_ptr<Tilemap>& tilemap);
    void CollisionRight(const std::unique_ptr<Tilemap>& tilemap);
    void CollisionHead(const std::unique_ptr<Tilemap>& tilemap);
private:
    //Movement
    MOVEMENT nextMovement{ MOVEMENT::IDLE };
    
};


