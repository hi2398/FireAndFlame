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

Direction Actor::GetDirection() const {
    return direction;
}

bool Actor::IsGrounded() {
    return grounded;
}
