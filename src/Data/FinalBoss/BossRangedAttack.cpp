//
// Created by Ashty on 29.07.2021.
//

#include "BossRangedAttack.h"
#include "../../Global.h"

BossRangedAttack::BossRangedAttack(Vector2 pos) : Interactable(InteractableType::FinalBossAttack){
    position = pos;
    texture = LoadTexture("assets/Bosses/FinalBoss/TEMP/rangedAttackFinalBoss.png");
    attackPoint = playerCharacter->GetPosition();
}

void BossRangedAttack::Interact(Actor &actor) {
    playerCharacter->SetHealth(playerCharacter->GetHealth()-10);
    markedDestroy = true;
}

void BossRangedAttack::Update() {
    --existCounter;
    moveTowardsPosition = {position.x - attackPoint.x,position.y - attackPoint.y};
    position = {position.x-(moveTowardsPosition.x/magnitude),position.y-(moveTowardsPosition.y/magnitude)};
    attackPoint = {attackPoint.x-(moveTowardsPosition.x/magnitude), attackPoint.y-(moveTowardsPosition.y/magnitude)};
    interactionZone = {position.x,position.y,(float)texture.width,(float)texture.height};
}

void BossRangedAttack::Draw() {
    DrawTexture(texture,position.x,position.y,WHITE);
}
