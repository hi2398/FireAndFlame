#include <raylib.h>
#include "Actor.h"

Actor::Actor(ObjectTypes type) : Object(type), lastTickPos(position) {

}

Vector2 Actor::GetLastPosition() {
    return lastTickPos;
}

