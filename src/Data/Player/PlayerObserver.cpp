#include "PlayerObserver.h"

#include "../../Global.h"

PlayerObserver::PlayerObserver(Actor &actor) : Observer(actor) {

}

PlayerObserver::~PlayerObserver() = default;

void PlayerObserver::OnNotify(Event event) {
    switch (event) {

        case Event::MOVE_LEFT:
            playerCharacter->Move(-3.f);
            break;
        case Event::MOVE_RIGHT:
            playerCharacter->Move(3.f);
            break;
        case Event::JUMP:
            //TODO: implement jump
            // playerCharacter->Jump();
            break;
    }
}
