#include "IdleGroundedSubState.h"
#include "MovingGroundedSubState.h"
#include <raymath.h>
#include <iostream>
#include "../../Global.h"

IdleGroundedSubState::IdleGroundedSubState(Actor& player) : PlayerStates(player) {
    if (player.GetIsDashing()) {
        activeFrame.y = 32 * 2;
    }
}

std::shared_ptr<State> IdleGroundedSubState::Update(Actor& player) {
    if constexpr (DEBUG_PLAYER_STATES) {
        std::cout << "Idle Grounded\n";
    }
    switch (player.GetNextMovement()) {
    case MOVEMENT::MOVE_LEFT:
        case MOVEMENT::MOVE_RIGHT:
        return std::make_shared<MovingGroundedSubState>(player);
    case MOVEMENT::IDLE:
        activeFrame = { (float)32 * playerCharacter->GetCurrentFrame(), 0, (float)32 * player.GetDirection(), 32 };
        return shared_from_this();
    case MOVEMENT::DASH_LEFT:
    case MOVEMENT::DASH_RIGHT:
        return std::make_shared<MovingGroundedSubState>(player);
    }
}

void IdleGroundedSubState::Draw(Actor& player) {
        DrawTextureRec(playerCharacter->lowerBody,
                       activeFrame,
                         player.GetPosition(),
                           WHITE);
}