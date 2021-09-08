#include "BossEnergySwordAttack.h"
#include "../../Global.h"

BossEnergySwordAttack::BossEnergySwordAttack(Vector2 position, bool attackDirection, int prepareCounter) : Interactable(InteractableType::FinalBossAttack){
    this->position = position;
    direction = attackDirection;
    this->prepareCounter = prepareCounter;
    texture = LoadTexture("assets/Bosses/FinalBoss/EnergyWall.png");

    if(direction){
        attackPoint = position;
        attackPoint.x = attackPoint.x-160;
    } else {
        attackPoint = position;
        attackPoint.x = attackPoint.x+160;
    }

    soundManager->PlaySfx(SFX::FB_SPEECH3);
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
    --counter;
    if(counter<=0){
        switch ((int)drawBox.x) {
            case 0: drawBox.x = 32;
                break;
            case 32: drawBox.x = 64;
                break;
            case 64: drawBox.x = 0;
                break;
            default:
                break;
        }
        counter = 20;
    }
}

void BossEnergySwordAttack::Draw() {
    DrawTextureRec(texture,drawBox,position,WHITE);
}
