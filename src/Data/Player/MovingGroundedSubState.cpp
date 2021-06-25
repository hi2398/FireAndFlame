#include "MovingGroundedSubState.h"
#include "IdleGroundedSubState.h"
#include "../../Global.h"

std::shared_ptr<State> MovingGroundedSubState::Update(Actor &actor) {
    const auto actorLastPos = actor.GetLastPosition(); //func alias
    const auto actorPos = actor.GetPosition(); //func alias

    std::cout << "Moving Grounded\n";
    switch (actor.GetNextMovement())
    {
    case MOVEMENT::MOVE_LEFT:
        if (!playerCharacter->GetWallCollisionLeft()) {
            actor.SetPosition({ actor.GetPosition().x - 3.0f, actor.GetPosition().y });
        }
        return shared_from_this();
    case MOVEMENT::MOVE_RIGHT:
        if (!playerCharacter->GetWallCollisionRight()) {
            actor.SetPosition({ actor.GetPosition().x + 3.0f, actor.GetPosition().y });
        }
        return shared_from_this();
    case MOVEMENT::IDLE:
        return std::make_shared<IdleGroundedSubState>();
    }

    
    
    
    
}

void MovingGroundedSubState::Draw(Actor& actor) {

}