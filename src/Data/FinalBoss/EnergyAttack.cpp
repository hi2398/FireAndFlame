#include "EnergyAttack.h"
#include "../../Global.h"

EnergyAttack::EnergyAttack(Vector2 position): Interactable(InteractableType::FinalBossAttack){
    texture = LoadTexture("assets/Bosses/FinalBoss/EnergyAttack.png");
    energyAttackPosition = position;
    attackPoint = {playerCharacter->GetPosition().x,playerCharacter->GetPosition().y};
    interactionZone = {energyAttackPosition.x,energyAttackPosition.y,(float)texture.width,(float)texture.height};
    magnitude = GetRandomValue(50,150);
}

void EnergyAttack::Interact(Actor &actor) {
    if(allowedToDamagePlayer){
        playerCharacter->SetHealth(playerCharacter->GetHealth()-10);
        markedDestroy = true;
    }
}

void EnergyAttack::Update() {
    --prepareCounter;
    if(prepareCounter <= 10){
        allowedToDamagePlayer = true;
        moveTowardsPosition = {energyAttackPosition.x - attackPoint.x,energyAttackPosition.y - attackPoint.y};
        energyAttackPosition = {energyAttackPosition.x-(moveTowardsPosition.x/magnitude),energyAttackPosition.y-(moveTowardsPosition.y/magnitude)};
        attackPoint = {playerCharacter->GetPosition().x,playerCharacter->GetPosition().y};
        attackPoint = {attackPoint.x-(moveTowardsPosition.x/2), attackPoint.y-(moveTowardsPosition.y/2)};
    }
    if(prepareCounter <= -160){markedDestroy = true;}
    interactionZone = {energyAttackPosition.x+8,energyAttackPosition.y+8,16,16};
    --counter;
    if(counter <= 0){
        switch ((int)drawZone.x) {
            case 0: drawZone.x = 32;
            break;
            case 32: drawZone.x = 64;
            break;
            case 64: drawZone.x = 0;
        }
        counter = 20;
    }
}

void EnergyAttack::Draw() {
    DrawTextureRec(texture,drawZone,energyAttackPosition,WHITE);
}