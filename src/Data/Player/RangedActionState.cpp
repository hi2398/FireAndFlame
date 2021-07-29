#include <iostream>
#include "RangedActionState.h"
#include "../../Global.h"
#include "IdleActionState.h"
#include "MeleeActionState.h"

RangedActionState::RangedActionState(Actor& player) : PlayerStates(player) {

}

std::shared_ptr<State> RangedActionState::Update(Actor& player) {
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
            
                /*activeFrame = {(float) 32 * playerCharacter->GetCurrentFrame(), 32 * 4, (float)32 * playerCharacter->GetDirection(), 32};*/


            stateFrameCounter++;
            if (stateFrameCounter >= 4 && thisFrame < 2) {
                stateFrameCounter = 0;
                thisFrame++;
            }
            activeFrame = { (float)32 * thisFrame, 32 * 4, (float)32 * player.GetDirection(), 32 };
            
            if (!isShootingFireball) {
                //decrease player health when casting fireball
                playerCharacter->SetHealth(playerCharacter->GetHealth() - 2.0f);

                fireballDirection = playerCharacter->GetDirection();
                if (player.GetDirection() == 1)vectorFireball.x = player.GetPosition().x + 25;
                if (player.GetDirection() == -1)vectorFireball.x = player.GetPosition().x + 9;
                vectorFireball.y = player.GetPosition().y + 11;
            }
            isShootingFireball = true;
            if (isShootingFireball) {
                vectorFireball.x += 20.0f *fireballDirection;
                if (vectorFireball.x > ((float)GetScreenWidth() / 2) + player.GetPosition().x || vectorFireball.x < player.GetPosition().x - ((float)GetScreenWidth() / 2)) {
                    isShootingFireball = false;
                    return std::make_shared<IdleActionState>(player);
                }
            }

            for (auto &enemies: sceneManager->GetEnemies()) {
				if (CheckCollisionPointRec(vectorFireball, enemies->GetCollider())&&!enemies->IsInvulnerable()) {
                    enemies->ReceiveDamage(10);
                    enemies->SetInvulnerable(true);
				}
            }
            
            break;
        default:
            //TODO: handle ranged state
            break;
    }
    return shared_from_this();

}

void RangedActionState::Draw(Actor& player) {
    DrawCircle(static_cast<int>(vectorFireball.x), static_cast<int>(vectorFireball.y), 8.0f, RED);
    
    DrawTextureRec(playerCharacter->upperBody, activeFrame, {player.GetPosition()}, WHITE);
}