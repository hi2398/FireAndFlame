#include <raylib.h>
#include <raymath.h>
#include "Actor.h"

Actor::Actor(ObjectTypes type) : Object(type), lastTickPos(position) {

}

Vector2 Actor::GetLastPosition() {
    return lastTickPos;
}

void Actor::Move(float distance) {
    position.x+=distance;
}

void Actor::Jump() {
    position.y -= 1.0f;
}

Direction Actor::GetDirection() const {
    return direction;
}

float Actor::GetGravityMultiplier() {
    return gravityMultiplier;
}

void Actor::SetGrounded(bool grounded)
{
    this->grounded = grounded;
}

bool Actor::IsGrounded() {
    return grounded;
}

void Actor::SetJumpCommand(bool jumpUp) {
    this->jumpUp = jumpUp;
}

bool Actor::GetJumpCommand() {
    return jumpUp;
}