#pragma once
#include <vector>
#include "Object.h"
#include "Component.h"
#include "raylib.h"

enum Direction{LEFT=-1, RIGHT=1};
enum class MOVEMENT { MOVE_LEFT, MOVE_RIGHT, IDLE };

class Actor : public Object {
public:
    explicit Actor(ObjectTypes type);
    void Update() override = 0;
    void Draw() override = 0;
    ~Actor() override=default;

    void Jump();
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

private:
    //Movement
    MOVEMENT nextMovement{ MOVEMENT::IDLE };
    
};


