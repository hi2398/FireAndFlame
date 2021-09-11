#include "IceBoss.h"
#include "raymath.h"
#include "../../Global.h"
#include "IBBeforeFight.h"

const float* IceBoss::multiplier;

IceBoss::IceBoss(Vector2 location) : Enemy(EnemyTypes::Boss) {
    health=maxHealth;
    SetPosition(location);
    texture=LoadTexture("assets/Bosses/IceBoss/Ice_Boss_Spritesheet.png");
    state = std::make_unique<IBBeforeFight>(*this);
    IceBoss::multiplier=&normalMultiplier; //set multiplier to point to the normal multiplier until boss goes into aggressive mode
    meleeRange.x=position.x-16;
    meleeRange.y=position.y;
}

void IceBoss::Update() {

    //states needed: part breaking, melee attack, ranged attack, pause(spawn minions+throw three barrels), seek player
    //all actions need an speed multiplier for aggression
    state=state->Update(*this);
    meleeRange.x=position.x-16;
    meleeRange.y=position.y;

    UpdateCollider(0,0, 32, 32);
    hud->SetBossEnemyHealth(health, 10);
    if (invulnerable) {
        invulnerableCounter++;
        if (invulnerableCounter >= 30) {
            invulnerableCounter = 0;
            invulnerable = false;
        }
    }
}

void IceBoss::Draw() {

    //draw boss itself
    state->Draw(*this);

}

void IceBoss::ReceiveDamage(int damage) {
    health-=damage;
    if(health<=7) {
        phase=3;
        multiplier=&aggressionMultiplier;
    } else if (health<=14) {
        phase=2;
        multiplier=&aggressionMultiplier;
    } else if (health<=21) {
        phase=1;
    }
    if (health<=0) markedDestroy=true;
}

bool IceBoss::Decide() {
        static const int shift = static_cast<int>(std::log2(RAND_MAX));
        return (rand() >> shift) & 1;
}

float IceBoss::SpeedMultiplier() {
    return *multiplier;
}

Rectangle IceBoss::GetMeleeRange() {
    return meleeRange;
}


float IceBoss::GetMovementSpeed() {
    return movementSpeed;
}

int IceBoss::GetPhase() {
    return phase;
}


