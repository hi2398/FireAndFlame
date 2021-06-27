#include "JumpingSubState.h"
#include "FallingSubState.h"
#include "../../Global.h"

std::shared_ptr<State> JumpingSubState::Update(Actor &actor) {
    const auto actorLastPos = actor.GetLastPosition(); //func alias
    const auto actorPos = actor.GetPosition(); //func alias

    //go to falling state if hit head
    if (actor.GetHeadCollision()) {
        actor.SetJumpSpeed(5.0f);
        return std::make_shared<FallingSubState>();
    }

    //move sideways while airborne
    switch (actor.GetNextMovement())
    {
    case MOVEMENT::MOVE_LEFT:
        if (!actor.GetWallCollisionLeft()) {
            if (actor.GetIsRunning()) {
                actor.SetPosition({ actor.GetPosition().x - 5.0f, actor.GetPosition().y });
            }
            else {
                actor.SetPosition({ actor.GetPosition().x - 3.0f, actor.GetPosition().y });
            }
        }
        break;
    case MOVEMENT::MOVE_RIGHT:
        if (!actor.GetWallCollisionRight()) {
            if (actor.GetIsRunning()) {
                actor.SetPosition({ actor.GetPosition().x + 5.0f, actor.GetPosition().y });
            }
            else {
                actor.SetPosition({ actor.GetPosition().x + 3.0f, actor.GetPosition().y });
            }
        }
        break;
    }

	if constexpr (DEBUG_BUILD) {
		std::cout << "New State: Jumping    " << std::endl;
	}

    //actual jumping stuff
    if(actor.GetJumpCommand()) {
        //check if actor is allowed to perform Double Jump
        if (actor.GetCanDoubleJump()) {
            switch (actor.GetTimesJumped())
            {
            case 1:
                actor.SetPosition({ actor.GetPosition().x, actor.GetPosition().y - actor.GetJumpSpeed() });
                actor.SetJumpSpeed(actor.GetJumpSpeed() - 0.1f * actor.GetGravityMultiplier());
                if (actor.GetJumpSpeed() <= 0) {
                    actor.SetJumpSpeed(5.0f);
                    actor.SetJumpCommand(false);
                    return std::make_shared<FallingSubState>();
                }
                break;
            case 2:
                actor.SetPosition({ actor.GetPosition().x, actor.GetPosition().y - actor.GetJumpSpeed() });
                actor.SetJumpSpeed(actor.GetJumpSpeed() - 0.1f * actor.GetGravityMultiplier());
                if (actor.GetJumpSpeed() <= 0) {
                    actor.SetJumpSpeed(5.0f);
                    actor.SetJumpCommand(false);
                    return std::make_shared<FallingSubState>();
                }
                break;
            default:
                break;
            }

            
        }
        else { //actor can only jump once
            if (actor.GetTimesJumped() == 1) {
				actor.SetPosition({ actor.GetPosition().x, actor.GetPosition().y - actor.GetJumpSpeed() });
				actor.SetJumpSpeed(actor.GetJumpSpeed() - 0.1f * actor.GetGravityMultiplier());
				if (actor.GetJumpSpeed() <= 0) {
					actor.SetJumpSpeed(5.0f);
					actor.SetJumpCommand(false);
					return std::make_shared<FallingSubState>();
				}
            }
            
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