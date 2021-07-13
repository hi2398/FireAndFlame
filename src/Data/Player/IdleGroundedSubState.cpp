#include "IdleGroundedSubState.h"
#include "MovingGroundedSubState.h"
#include <raymath.h>
#include <iostream>
#include "../../Global.h"

std::shared_ptr<State> IdleGroundedSubState::Update(Actor &actor) {
    const auto actorLastPos = actor.GetLastPosition(); //func alias
    const auto actorPos = actor.GetPosition(); //func alias

    if constexpr (DEBUG_PLAYER_STATES) {
        std::cout << "Idle Grounded\n";
    }
    switch (actor.GetNextMovement())
    {
    case MOVEMENT::MOVE_LEFT:
        return std::make_shared<MovingGroundedSubState>();
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
    switch (actor.GetDirection()) {
    case LEFT:
        DrawTextureRec(playerCharacter->texturePlayer, { 0, 0, (float)-playerCharacter->texturePlayer.width, (float)playerCharacter->texturePlayer.height }, { playerCharacter->GetPosition().x, playerCharacter->GetPosition().y }, WHITE);
        break;
    case RIGHT:
        DrawTextureRec(playerCharacter->texturePlayer, { 0, 0, (float)playerCharacter->texturePlayer.width, (float)playerCharacter->texturePlayer.height }, { playerCharacter->GetPosition().x, playerCharacter->GetPosition().y }, WHITE);
        break;
    }
}