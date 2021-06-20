#include "PlayerObserver.h"

#include "../../Global.h"

PlayerObserver::PlayerObserver(Actor &actor) : Observer(actor) {

}

PlayerObserver::~PlayerObserver() = default;

void PlayerObserver::OnNotify(Event event) {
    switch (event) {

        case Event::MOVE_LEFT:
            break;
        case Event::MOVE_RIGHT:
            playerCharacter->Move(1);
            break;
        case Event::JUMP:
            break;
    }
}
