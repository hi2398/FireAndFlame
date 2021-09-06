#include "BossEnergySwordAttack.h"
#include "../../Global.h"

BossEnergySwordAttack::BossEnergySwordAttack(Vector2 position, bool attackDirection, int prepareCounter) : Interactable(InteractableType::FinalBossAttack){
    this->position = position;
    direction = attackDirection;
    this->prepareCounter = prepareCounter;
    texture = LoadTexture("assets/Bosses/FinalBoss/TEMP/Energywall.png");

    if(direction){
        attackPoint = position;
        attackPoint.x = attackPoint.x-160;
    } else {
        attackPoint = position;
        attackPoint.x = attackPoint.x+160;
    }
}

void BossEnergySwordAttack::Interact(Actor &actor) {
    if(!playerCharacter->IsInvulnerable()) {
        playerCharacter->SetHealth(playerCharacter->GetHealth() - 10);
        playerCharacter->SetInvulnerable(true);
    }
}

void BossEnergySwordAttack::Update() {
    --prepareCounter;
    interactionZone = {position.x,position.y,(float)texture.width,(float)texture.height};
    if(prepareCounter <= 0){
        moveTowardsPosition = {position.x - attackPoint.x,position.y - attackPoint.y};
        position = {position.x-(moveTowardsPosition.x/magnitude),position.y-(moveTowardsPosition.y/magnitude)};
        attackPoint = {attackPoint.x-(moveTowardsPosition.x/magnitude), attackPoint.y-(moveTowardsPosition.y/magnitude)};
    }
    if(prepareCounter < -200){
        markedDestroy = true;
    }
}

void BossEnergySwordAttack::Draw() {
    DrawTexture(texture,position.x,position.y,WHITE);
}
