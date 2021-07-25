#include "SpearAttack.h"
#include "../../Global.h"

SpearAttack::SpearAttack(Vector2 position) : Interactable(InteractableType::FinalBossAttack){
    interactionZone = {position.x,position.y,32,10};
    spearPosition = {position.x,position.y};
    texture = LoadTexture("assets/graphics/Enemies/BossEnemies/spear.png");
}

void SpearAttack::Interact(Actor &actor){
    if(!hasDamagedPlayer && damageActive){
        hasDamagedPlayer = true;
        playerCharacter->SetHealth(playerCharacter->GetHealth()-5);
    }
}

void SpearAttack::Update() {
    if(!fixAttack) {
        spearRotation = atan2(playerCharacter->GetPosition().y - spearPosition.y,
                              playerCharacter->GetPosition().x - spearPosition.x) * 180 / PI;
    }else if(prepareCounter <= 0){
        damageActive = true;
        moveTowardsPosition = {spearPosition.x - attackPoint.x,spearPosition.y - attackPoint.y};
        spearPosition = {spearPosition.x-(moveTowardsPosition.x/magnitude),spearPosition.y-(moveTowardsPosition.y/magnitude)};
        attackPoint = {attackPoint.x-(moveTowardsPosition.x/magnitude), attackPoint.y-(moveTowardsPosition.y/magnitude)};
    }
    --prepareCounter;
    if(prepareCounter <= 30 && !fixAttack){
        attackPoint = {playerCharacter->GetPosition().x,playerCharacter->GetPosition().y};
        fixAttack = true;
    }
    if(prepareCounter < -60){
        markedDestroy = true;
    }
    interactionZone = {spearPosition.x,spearPosition.y,(float)texture.width,(float)texture.height};
}

void SpearAttack::Draw() {
    DrawTextureEx(texture,spearPosition,spearRotation,1,WHITE);
}
