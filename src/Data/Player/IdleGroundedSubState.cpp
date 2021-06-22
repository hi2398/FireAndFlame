#include "IdleGroundedSubState.h"
#include "MovingGroundedSubState.h"
#include <raymath.h>
#include "../../Global.h"

std::shared_ptr<State> IdleGroundedSubState::Update(Actor &actor) {
    const auto actorLastPos = actor.GetLastPosition(); //func alias
    const auto actorPos = actor.GetPosition(); //func alias

    if((actorLastPos.x==actorPos.x) && (actorLastPos.y==actorPos.y)) {
        //TODO: do idle stuff here
        return shared_from_this();
    } else {
        if constexpr(DEBUG_BUILD) {
            std::cout << "New State: Moving Grounded" << std::endl;
        }
        return std::make_shared<MovingGroundedSubState>();
    }

}
