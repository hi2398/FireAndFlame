#include "SpearAttack.h"
#include "../../Global.h"
#include "raymath.h"

SpearAttack::SpearAttack(Vector2 position) : Interactable(InteractableType::FinalBossAttack){
    texture = LoadTexture("assets/graphics/Enemies/BossEnemies/BossSpearAttack.png");
    interactionZone = {position.x,position.y - 16,32,32};
    spearPosition = {position.x,position.y};
    spearMiddle = {spearPosition.x + (float)texture.width / 2, spearPosition.y + (float)texture.height / 2 };
    attackPoint = { playerCharacter->GetPosition().x + 16,playerCharacter->GetPosition().y + 16 };
}

void SpearAttack::Interact(Actor &actor){
    if(!playerCharacter->IsInvulnerable() && damageActive){
        if (CheckCollisionLines(spearMiddle, spearTip, { playerCharacter->GetPosition().x + 16, playerCharacter->GetPosition().y }, { playerCharacter->GetPosition().x + 16, playerCharacter->GetPosition().y + 32}, pseudoPointer) 
            || CheckCollisionLines(spearMiddle, spearTip, { playerCharacter->GetPosition().x + 6, playerCharacter->GetPosition().y + 16}, { playerCharacter->GetPosition().x + 26, playerCharacter->GetPosition().y + 16 }, pseudoPointer)) {
            playerCharacter->SetInvulnerable(true);
            playerCharacter->SetHealth(playerCharacter->GetHealth()-5);
            }
    }
}

void SpearAttack::Update() {
    pseudoPointer = {};
    if(!fixAttack) {
        spearRotation = atan2(playerCharacter->GetPosition().y + 16- spearMiddle.y,
                              playerCharacter->GetPosition().x + 16- spearMiddle.x) * 180 / PI;
    }else if(prepareCounter <= 0){
        damageActive = true;
        moveTowardsPosition = {spearMiddle.x - attackPoint.x,spearMiddle.y - attackPoint.y};
        spearPosition = {spearPosition.x-(moveTowardsPosition.x/magnitude),spearPosition.y-(moveTowardsPosition.y/magnitude)};
        attackPoint = {attackPoint.x-(moveTowardsPosition.x/magnitude), attackPoint.y-(moveTowardsPosition.y/magnitude)};
    }
    --prepareCounter;
    if(prepareCounter <= 45 && !fixAttack){
        attackPoint = {playerCharacter->GetPosition().x + 16,playerCharacter->GetPosition().y+ 16};
        fixAttack = true;
    }
    if(prepareCounter < -60){
        markedDestroy = true;
    }
    interactionZone = {spearPosition.x,spearPosition.y-16,(float)texture.width,(float)texture.width};
    rotationPoint = {(float)texture.width / 2, (float)texture.height / 2 };
    spearMiddle = { spearPosition.x + (float)texture.width / 2, spearPosition.y + (float)texture.height / 2 };
    spearTip = Vector2Add(spearMiddle, Vector2Scale(Vector2Normalize(Vector2Subtract(attackPoint, spearMiddle)), 30));
}

void SpearAttack::Draw() {
    DrawTexturePro(texture, { 0,0,(float)texture.width, (float)texture.height }, {spearPosition.x+ (float)texture.width/2, spearPosition.y + (float)texture.height / 2 ,(float)texture.width, (float)texture.height }, rotationPoint, spearRotation, WHITE);
}

SpearAttack::~SpearAttack()
{
    UnloadTexture(texture);
}
