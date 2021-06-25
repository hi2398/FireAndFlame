#include "MovementState.h"
#include "IdleGroundedSubState.h"
#include "JumpingSubState.h"


#include <iostream>



MovementState::MovementState() {
    groundedSubState=std::make_shared<IdleGroundedSubState>();
    aerialSubState=std::make_shared<JumpingSubState>();
}

std::shared_ptr<State> MovementState::Update(Actor &actor) {
    if (actor.IsGrounded()) {
        actor.SetFallingSpeed(0.0f);
        groundedSubState=groundedSubState->Update(actor); //IdleGroundedSubState or MovingGroundedSubState
    } else {
        aerialSubState=aerialSubState->Update(actor); //FallingSubState or JumpingSubState
    }


    return shared_from_this(); //always return this, acts as a container
}

void MovementState::Draw(Actor& actor) {

}