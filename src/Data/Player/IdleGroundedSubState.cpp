#include "IdleGroundedSubState.h"
#include "MovingGroundedSubState.h"
#include <raymath.h>
#include "../../Global.h"

std::shared_ptr<State> IdleGroundedSubState::Update(Actor &actor) {
    const auto actorLastPos = actor.GetLastPosition(); //func alias
    const auto actorPos = actor.GetPosition(); //func alias

    std::cout << "Idle Grounded\n";
    switch (actor.GetNextMovement())
    {
    case MOVEMENT::MOVE_LEFT:
        return std::make_shared<MovingGroundedSubState>();
    case MOVEMENT::MOVE_RIGHT:
        return std::make_shared<MovingGroundedSubState>();
    case MOVEMENT::IDLE:
        return shared_from_this();
    }

    //if(actorLastPos.x==actorPos.x && actorLastPos.y==actorPos.y) {
    //    //TODO: do idle stuff here
    //    std::cout << "check idle\n";
    //    return shared_from_this();
    //} else {
    //    if constexpr(DEBUG_BUILD) {
    //        std::cout << "leaving idle\n";
    //        std::cout << "New State: Moving Grounded" << std::endl;
    //    }
    //    return std::make_shared<MovingGroundedSubState>();
    //}

}

void IdleGroundedSubState::Draw(Actor& actor) {

}