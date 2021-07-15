#include "IdleGroundedSubState.h"
#include "MovingGroundedSubState.h"
#include <raymath.h>
#include <iostream>
#include "../../Global.h"

std::shared_ptr<State> IdleGroundedSubState::Update(Actor &actor) {

    if constexpr (DEBUG_PLAYER_STATES) {
        std::cout << "Idle Grounded\n";
    }
    switch (actor.GetNextMovement()) {
    case MOVEMENT::MOVE_LEFT:
        case MOVEMENT::MOVE_RIGHT:
        return std::make_shared<MovingGroundedSubState>();
    case MOVEMENT::IDLE:
        return shared_from_this();
        case MOVEMENT::DASH_LEFT:
            case MOVEMENT::DASH_RIGHT:
                return std::make_shared<MovingGroundedSubState>();
    }
}

void IdleGroundedSubState::Draw(Actor& actor) {
        DrawTextureRec(playerCharacter->texturePlayer,
                       { 0,
                         0,
                         (float)playerCharacter->texturePlayer.width*actor.GetDirection(),
                         (float)playerCharacter->texturePlayer.height },
                         playerCharacter->GetPosition(),
                           WHITE);
}