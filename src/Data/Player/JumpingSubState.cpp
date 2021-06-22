#include "JumpingSubState.h"
#include "FallingSubState.h"
#include "../../Global.h"

std::shared_ptr<State> JumpingSubState::Update(Actor &actor) {
    const auto actorLastPos = actor.GetLastPosition(); //func alias
    const auto actorPos = actor.GetPosition(); //func alias

    if(actorLastPos.y<=actorPos.y) {
        //TODO: do jumping state stuff
        return shared_from_this();
    } else {
        if constexpr(DEBUG_BUILD) {
            std::cout << "New State: Falling" << std::endl;
        }
        return std::make_shared<FallingSubState>();
    }

}
