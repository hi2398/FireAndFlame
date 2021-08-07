#include <iostream>
#include "RangedActionState.h"
#include "../../Global.h"
#include "IdleActionState.h"
#include "MeleeActionState.h"
#include "Fireball.h"

RangedActionState::RangedActionState(Actor& player) : PlayerStates(player) {

}

std::shared_ptr<State> RangedActionState::Update(Actor& player) {
    if (player.GetActionBlocked() || player.GetIsDashing()) return std::make_shared<IdleActionState>(player);
    switch (playerCharacter->GetNextAction()) {
        case ACTION::MELEE_ATTACK:
            if (actionDone) {
                if constexpr(DEBUG_PLAYER_STATES) {
                    std::cout << "new state: melee" << std::endl;
                }
                return std::make_shared<MeleeActionState>(player);
            }
        case ACTION::NONE:
            if (actionDone) {
                if constexpr(DEBUG_PLAYER_STATES) {
                    std::cout << "new state: idle action" << std::endl;
                }
                return std::make_shared<IdleActionState>(player);
            }
        case ACTION::RANGED_ATTACK:
            stateFrameCounter++;

            //player frames
            if (stateFrameCounter >= 4 && thisFrame < 2) {
                stateFrameCounter = 0;
                thisFrame++;
            }
			activeFrame = { (float)32 * thisFrame, 32 * 4, (float)32 * player.GetDirection(), 32 };
            
            
            if (!isShootingFireball) {
                //decrease player health when casting fireball
                playerCharacter->SetHealth(playerCharacter->GetHealth() - 5.0f);

                fireballDirection = playerCharacter->GetDirection();
                if (player.GetDirection() == 1)vectorFireball.x = player.GetPosition().x + 25;
                if (player.GetDirection() == -1)vectorFireball.x = player.GetPosition().x + 9;
                vectorFireball.y = player.GetPosition().y;

                sceneManager->AddInteractable(std::make_unique<Fireball>(vectorFireball, fireballDirection, player.GetType()));
            }
            isShootingFireball = true;
            if (isShootingFireball) {
                actionCounter++;
                if (actionCounter >= 20) return std::make_shared<IdleActionState>(player);
            }
            
            break;
        default:
            //TODO: handle ranged state
            break;
    }
    return shared_from_this();

}

void RangedActionState::Draw(Actor& player) { 
    DrawTextureRec(playerCharacter->upperBody, activeFrame, {player.GetPosition()}, WHITE);
}