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

    void Move(float distance);
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

protected:
    Vector2 lastTickPos;
    Direction direction{RIGHT};
    bool grounded{false};
    float gravityMultiplier = 1.0f;
    bool jumpUp = false;


    

private:
    //Movement
    MOVEMENT nextMovement{ MOVEMENT::IDLE };
};


