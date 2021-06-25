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
            playerCharacter->SetJumpCommand(true);
            playerCharacter->Jump();
            break;
        case EVENT::MELEE_ATTACK:
            playerCharacter->SetNextAction(ACTION::MELEE_ATTACK);
            break;
        case EVENT::RANGED_ATTACK:
            playerCharacter->SetNextAction(ACTION::RANGED_ATTACK);
    }
}
