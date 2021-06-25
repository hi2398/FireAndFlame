#include <raylib.h>
#include <raymath.h>
#include "Actor.h"

Actor::Actor(ObjectTypes type) : Object(type), lastTickPos(position) {

}

void Actor::SetLastPosition(Vector2 position) {
    lastTickPos = position;
}

Vector2 Actor::GetLastPosition() {
    return lastTickPos;
}

void Actor::Move(float distance) {
    position.x+=distance;
}

void Actor::Jump() {
    position.y -= 10.0f;
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

MOVEMENT Actor::GetNextMovement() {
    MOVEMENT tmp = nextMovement;
    nextMovement = MOVEMENT::IDLE;
    return tmp;
}

void Actor::SetNextMovement(MOVEMENT movement) {
    nextMovement = movement;
}

bool Actor::GetWallCollisionLeft() {
    return hugWallLeft;
}

void Actor::SetWallCollisionLeft(bool hugWallLeft) {
    this->hugWallLeft = hugWallLeft;
}

bool Actor::GetWallCollisionRight() {
    return hugWallRight;
}

void Actor::SetWallCollisionRight(bool hugWallRight) {
    this->hugWallRight = hugWallRight;
}

float Actor::GetFallingSpeed() {
    return fallingSpeed;
}

void Actor::SetFallingSpeed(float fallingSpeed) {
    this->fallingSpeed = fallingSpeed;
}

bool Actor::GetHeadCollision() {
    return headCollision;
}

void Actor::SetHeadCollision(bool headCollision) {
    this->headCollision = headCollision;
}