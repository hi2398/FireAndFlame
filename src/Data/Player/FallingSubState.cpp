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
        if (!playerCharacter->GetWallCollisionLeft()) {
            actor.SetPosition({ actor.GetPosition().x - 3.0f, actor.GetPosition().y });
        }
        break;
    case MOVEMENT::MOVE_RIGHT:
        if (!playerCharacter->GetWallCollisionRight()) {
            actor.SetPosition({ actor.GetPosition().x + 3.0f, actor.GetPosition().y });
        }
        break;
    }

    if constexpr (DEBUG_BUILD) {
        std::cout << "New State: Falling    " << std::endl;
    }

    if(!actor.GetJumpCommand()) {
        //TODO: do jumping stuff
        actor.SetPosition({actor.GetPosition().x, actor.GetPosition().y + actor.GetFallingSpeed()});
        if (actor.GetFallingSpeed() < 5.0f) actor.SetFallingSpeed(actor.GetFallingSpeed() + 0.1f * actor.GetGravityMultiplier()) ;
        if (actor.GetFallingSpeed() >= 5.0f)actor.SetFallingSpeed(5.0f);
        return shared_from_this();
    } 
    else {
        actor.SetFallingSpeed(0.0f);
        return std::make_shared<JumpingSubState>();
    }
}

void FallingSubState::Draw(Actor& actor) {

}
