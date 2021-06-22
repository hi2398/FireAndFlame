#include "FallingSubState.h"
#include "../../Global.h"
#include "JumpingSubState.h"

std::shared_ptr<State> FallingSubState::Update(Actor &actor) {
    const auto actorLastPos = actor.GetLastPosition(); //func alias
    const auto actorPos = actor.GetPosition(); //func alias

    if(actorLastPos.y>actorPos.y) {
        //TODO: do jumping stuff
        return shared_from_this();
    } else {
        if constexpr(DEBUG_BUILD) {
            std::cout << "New State: Jumping" << std::endl;
        }
        return std::make_shared<JumpingSubState>();
    }
}
