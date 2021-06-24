#pragma once
#include <vector>
#include "Object.h"
#include "Component.h"
#include "raylib.h"

enum Direction{LEFT=-1, RIGHT=1};

class Actor : public Object {
public:
    explicit Actor(ObjectTypes type);
    void Update() override = 0;
    void Draw() override = 0;
    ~Actor() override=default;

    void Move(float distance);
    void Jump();
    Vector2 GetLastPosition();
    Direction GetDirection() const;
    float GetGravityMultiplier();
    void SetGrounded(bool grounded);
    bool IsGrounded();
    void SetJumpCommand(bool jumpUp);
    bool GetJumpCommand();

protected:
    Vector2 lastTickPos;
    Direction direction{RIGHT};
    bool grounded{false};
    float gravityMultiplier = 1.0f;
    bool jumpUp = false;


    

private:

};


