#include "MovementState.h"
#include "IdleGroundedSubState.h"
#include "JumpingSubState.h"
#include "PlayerCharacter.h"

#include <iostream>



MovementState::MovementState(Actor& player) : PlayerStates(player) {
    groundedSubState=std::make_shared<IdleGroundedSubState>(player);
    aerialSubState=std::make_shared<JumpingSubState>(player);
}

std::shared_ptr<State> MovementState::Update(Actor& player) {
    player.SetActionBlocked(false);
    if (player.IsGrounded()) {
        aerialSubState = std::make_shared<JumpingSubState>(player);
        player.SetCanDash(true);
        player.SetWallCounter(0);
        player.SetTimesJumped(0);
        player.SetJumpCommand(false);
        player.SetWallJumpCommand(false);
        player.SetJumpSpeed(5.0f);
        player.SetFallingSpeed(0.0f);
        groundedSubState=groundedSubState->Update(player); //IdleGroundedSubState or MovingGroundedSubState
    } else {
        groundedSubState = std::make_shared<IdleGroundedSubState>(player);
        aerialSubState=aerialSubState->Update(player); //FallingSubState or JumpingSubState
    }


    return shared_from_this(); //always return this, acts as a container
}

void MovementState::Draw(Actor& player) {
    if (player.IsGrounded()) {
        groundedSubState->Draw(player); //IdleGroundedSubState or MovingGroundedSubState
    }
    else {
        aerialSubState->Draw(player); //FallingSubState or JumpingSubState
    }
}