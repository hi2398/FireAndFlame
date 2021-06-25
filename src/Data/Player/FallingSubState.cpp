#include "FallingSubState.h"
#include "../../Global.h"
#include "JumpingSubState.h"

std::shared_ptr<State> FallingSubState::Update(Actor &actor) {
    const auto actorLastPos = actor.GetLastPosition(); //func alias
    const auto actorPos = actor.GetPosition(); //func alias

    //move sideways while airborne
    switch (actor.GetNextMovement())
    {
    case MOVEMENT::MOVE_LEFT:
        actor.SetPosition({ actor.GetPosition().x - 3.0f, actor.GetPosition().y });
        break;
    case MOVEMENT::MOVE_RIGHT:
        actor.SetPosition({ actor.GetPosition().x + 3.0f, actor.GetPosition().y });
        break;
    }

    if constexpr (DEBUG_BUILD) {
        std::cout << "New State: Falling    " << std::endl;
    }

    if(!actor.GetJumpCommand()) {
        //TODO: do jumping stuff
        actor.SetPosition({actor.GetPosition().x, actor.GetPosition().y + fallingSpeed});
        if (fallingSpeed < 3.0f)fallingSpeed += 0.1f * actor.GetGravityMultiplier();
        if (fallingSpeed >= 3.0f)fallingSpeed = 3.0f;
        return shared_from_this();
    } 
    else {
        fallingSpeed = 0.0f;
        return std::make_shared<JumpingSubState>();
    }
}

void FallingSubState::Draw(Actor& actor) {

}
