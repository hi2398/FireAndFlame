#include "RangedActionState.h"
#include "../../Global.h"
#include "IdleActionState.h"
#include "MeleeActionState.h"

std::shared_ptr<State> RangedActionState::Update(Actor &actor) {
    switch (playerCharacter->GetNextAction()) {
        case ACTION::MELEE_ATTACK:
            if (actionDone) {
                if constexpr(DEBUG_BUILD) {
                    std::cout << "new state: melee" << std::endl;
                }
                return std::make_shared<MeleeActionState>();
            }
        case ACTION::NONE:
            if (actionDone) {
                if constexpr(DEBUG_BUILD) {
                    std::cout << "new state: idle action" << std::endl;
                }
                return std::make_shared<IdleActionState>();
            }
        case ACTION::RANGED_ATTACK:
            if (!isShootingFireball) {
                vectorFireball.x = playerCharacter->GetPosition().x + 25;
                vectorFireball.y = playerCharacter->GetPosition().y + 11;
            }
            isShootingFireball = true;
            if (isShootingFireball) {
                vectorFireball.x += 10.0f;
                if (vectorFireball.x > ((float)GetScreenWidth() / 2) + playerCharacter->GetPosition().x) {
                    isShootingFireball = false;
                    return std::make_shared<IdleActionState>();
                }
            }
        default:
            //TODO: handle ranged state
            return shared_from_this();
    }
    throw std::invalid_argument("bad state");
}

void RangedActionState::Draw(Actor& actor) {
    if (isShootingFireball) {
        DrawCircle(static_cast<int>(vectorFireball.x), static_cast<int>(vectorFireball.y), 8.0f, RED);
    }
}