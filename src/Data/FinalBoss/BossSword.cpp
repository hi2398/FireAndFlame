//
// Created by Ashty on 27.07.2021.
//

#include "BossSword.h"
#include "../../Global.h"

BossSword::BossSword(Vector2 position) : Interactable(InteractableType::FinalBossAttack){
    texture = LoadTexture("assets/Bosses/FinalBoss/TEMP/EndBossSword.png");
    this->position = position;
    targetPosition=position;
}

void BossSword::Interact(Actor &actor) {
    if(!hasDamagedPlayer){
        hasDamagedPlayer = true;
        damageCounter = 60;
        playerCharacter->SetHealth(playerCharacter->GetHealth()-10);
    }
}

void BossSword::Update() {
    interactionZone = {position.x,position.y,(float)texture.width,(float)texture.height};
    if(hasDamagedPlayer){
        --damageCounter;
        if(damageCounter <= 0){
            hasDamagedPlayer = false;
        }
    }
    moveTowardsPosition = {position.x - targetPosition.x,position.y - targetPosition.y};
    position = {position.x-(moveTowardsPosition.x/magnitude),position.y-(moveTowardsPosition.y/magnitude)};
}

void BossSword::Draw() {
    DrawTexture(texture,position.x,position.y,WHITE);
}

void BossSword::ChangeTarget(Vector2 targetedPosition) {
    targetPosition = targetedPosition;
}
