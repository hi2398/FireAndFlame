#include "MovementState.h"
#include "IdleGroundedSubState.h"
#include "JumpingSubState.h"


#include <iostream>



MovementState::MovementState() {
    groundedSubState=std::make_shared<IdleGroundedSubState>();
    aerialSubState=std::make_shared<JumpingSubState>();
}

std::shared_ptr<State> MovementState::Update(Actor &actor) {
    actor.SetActionBlocked(false);
    if (actor.IsGrounded()) {
        aerialSubState = std::make_shared<JumpingSubState>();
        actor.SetCanDash(true);
        actor.SetWallCounter(0);
        actor.SetTimesJumped(0);
        actor.SetJumpCommand(false);
        actor.SetWallJumpCommand(false);
        actor.SetJumpSpeed(5.0f);
        actor.SetFallingSpeed(0.0f);
        groundedSubState=groundedSubState->Update(actor); //IdleGroundedSubState or MovingGroundedSubState
    } else {
        aerialSubState=aerialSubState->Update(actor); //FallingSubState or JumpingSubState
    }


    return shared_from_this(); //always return this, acts as a container
}

void MovementState::Draw(Actor& actor) {
    if (actor.IsGrounded()) {
        groundedSubState->Draw(actor); //IdleGroundedSubState or MovingGroundedSubState
    }
    else {
        aerialSubState->Draw(actor); //FallingSubState or JumpingSubState
    }
}