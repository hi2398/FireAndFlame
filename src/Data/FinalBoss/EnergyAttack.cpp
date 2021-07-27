#include "EnergyAttack.h"
#include "../../Global.h"

EnergyAttack::EnergyAttack(Vector2 position): Interactable(InteractableType::FinalBossAttack){
    texture = LoadTexture("assets/Bosses/FinalBoss/TEMP/energy.png");
    energyAttackPosition = position;
    attackPoint = {playerCharacter->GetPosition().x,playerCharacter->GetPosition().y};
    interactionZone = {energyAttackPosition.x,energyAttackPosition.y,(float)texture.width,(float)texture.height};
    magnitude = GetRandomValue(50,150);
}

void EnergyAttack::Interact(Actor &actor) {
    if(!hasDamagedPlayer){
        hasDamagedPlayer = true;
        playerCharacter->SetHealth(playerCharacter->GetHealth()-10);
        markedDestroy = true;
    }
}

void EnergyAttack::Update() {
    --prepareCounter;
    if(prepareCounter <= 10){
        moveTowardsPosition = {energyAttackPosition.x - attackPoint.x,energyAttackPosition.y - attackPoint.y};
        energyAttackPosition = {energyAttackPosition.x-(moveTowardsPosition.x/magnitude),energyAttackPosition.y-(moveTowardsPosition.y/magnitude)};
        attackPoint = {playerCharacter->GetPosition().x,playerCharacter->GetPosition().y};
        attackPoint = {attackPoint.x-(moveTowardsPosition.x/2), attackPoint.y-(moveTowardsPosition.y/2)};
    }
    if(prepareCounter <= -200){markedDestroy = true;}
    interactionZone = {energyAttackPosition.x,energyAttackPosition.y,(float)texture.width,(float)texture.height};
}

void EnergyAttack::Draw() {
    DrawTexture(texture,energyAttackPosition.x,energyAttackPosition.y,WHITE);
}