
#include "EnergyAttack.h"
#include "../../Global.h"

EnergyAttack::EnergyAttack(Vector2 position): Interactable(InteractableType::FinalBossAttack){
    texture = LoadTexture("assets/Bosses/FinalBoss/TEMP/energy.png");
    energyAttackPosition = position;
    interactionZone = {energyAttackPosition.x,energyAttackPosition.y,(float)texture.width,(float)texture.height};
}

void EnergyAttack::Interact(Actor &actor) {
    if(!hasDamagedPlayer){
        hasDamagedPlayer = true;
        playerCharacter->SetHealth(playerCharacter->GetHealth()-10);
    }
}

void EnergyAttack::Update() {

}

void EnergyAttack::Draw() {
    DrawTexture(texture,energyAttackPosition.x,energyAttackPosition.y,WHITE);

}