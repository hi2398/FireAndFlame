#include "JumpingSubState.h"
#include "FallingSubState.h"
#include "../../Global.h"

std::shared_ptr<State> JumpingSubState::Update(Actor &actor) {
    const auto actorLastPos = actor.GetLastPosition(); //func alias
    const auto actorPos = actor.GetPosition(); //func alias

    //go to falling state if hit head
    if (actor.GetHeadCollision()) {
        return std::make_shared<FallingSubState>();
    }

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
		std::cout << "New State: Jumping    " << std::endl;
	}

    if(actor.GetJumpCommand()) {
		////TODO: do jumping state stuff
		actor.SetPosition({ actor.GetPosition().x, actor.GetPosition().y - actor.GetJumpSpeed() });
        actor.SetJumpSpeed(actor.GetJumpSpeed() - 0.1f * actor.GetGravityMultiplier());
        if (actor.GetJumpSpeed() <= 0) {
            actor.SetJumpSpeed(5.0f);
            actor.SetJumpCommand(false);
            return std::make_shared<FallingSubState>();
        }

        return shared_from_this();
    } else {
        if constexpr(DEBUG_BUILD) {
            std::cout << "New State: Falling    " << std::endl;
        }
        actor.SetJumpSpeed(5.0f);
        return std::make_shared<FallingSubState>();
    }

}

void JumpingSubState::Draw(Actor& actor) {
    
}