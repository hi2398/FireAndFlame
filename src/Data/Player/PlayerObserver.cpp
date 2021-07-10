#include "PlayerObserver.h"

#include "../../Global.h"

PlayerObserver::PlayerObserver(Actor &actor) : Observer(actor) {

}

PlayerObserver::~PlayerObserver() = default;

void PlayerObserver::OnNotify(EVENT event) {
    switch (event) {

        case EVENT::MOVE_LEFT:
            playerCharacter->SetNextMovement(MOVEMENT::MOVE_LEFT);
            break;
        case EVENT::MOVE_RIGHT:
            playerCharacter->SetNextMovement(MOVEMENT::MOVE_RIGHT);
            break;
        case EVENT::JUMP:
            if (!playerCharacter->GetJumpBlocked()) playerCharacter->SetJumpSpeed(5.0f);
            playerCharacter->SetTimesJumped(playerCharacter->GetTimesJumped()+1);
            playerCharacter->SetGrounded(false);
            playerCharacter->SetJumpCommand(true);
            break;
        case EVENT::MELEE_ATTACK:
            playerCharacter->SetAttackDirection(playerCharacter->GetDirection()),playerCharacter->SetNextAction(ACTION::MELEE_ATTACK);
            break;
        case EVENT::RANGED_ATTACK:
            playerCharacter->SetNextAction(ACTION::RANGED_ATTACK);
            break;
        case EVENT::WALL_JUMP:
            playerCharacter->SetWallJumpCommand(true);
            break;
        case EVENT::DASH_LEFT:
            playerCharacter->SetNextMovement(MOVEMENT::DASH_LEFT), playerCharacter->SetCanDash(false);
            break;
        case EVENT::DASH_RIGHT:
            playerCharacter->SetNextMovement(MOVEMENT::DASH_RIGHT), playerCharacter->SetCanDash(false);
            break;
    }
}
