#include "IdleGroundedSubState.h"
#include "MovingGroundedSubState.h"
#include <raymath.h>
#include <iostream>
#include "../../Global.h"

std::shared_ptr<State> IdleGroundedSubState::Update(Actor &actor) {
    auto player = static_cast<PlayerCharacter&>(actor);
    if constexpr (DEBUG_PLAYER_STATES) {
        std::cout << "Idle Grounded\n";
    }
    switch (player.GetNextMovement()) {
    case MOVEMENT::MOVE_LEFT:
        case MOVEMENT::MOVE_RIGHT:
        return std::make_shared<MovingGroundedSubState>();
    case MOVEMENT::IDLE:
        idleFrameCounter++;
        if (idleFrameCounter >= 15) {
            thisFrame++;
            idleFrameCounter = 0;
        }
        activeFrame = { (float)-32 * thisFrame, 0, (float)32 * playerCharacter->GetDirection(), 32 };
        return shared_from_this();
    case MOVEMENT::DASH_LEFT:
    case MOVEMENT::DASH_RIGHT:
        return std::make_shared<MovingGroundedSubState>();
    }
}

void IdleGroundedSubState::Draw(Actor& actor) {
    auto player = static_cast<PlayerCharacter&>(actor);
        DrawTextureRec(playerCharacter->spriteSheetMagmos,
                       activeFrame,
                         playerCharacter->GetPosition(),
                           WHITE);
}