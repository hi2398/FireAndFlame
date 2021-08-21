#include "IceBoss.h"
#include "raymath.h"
#include "../../Global.h"
#include "IBSeek.h"

const float* IceBoss::multiplier;

IceBoss::IceBoss(Vector2 location) : Enemy(EnemyTypes::Boss) {
    SetPosition(location);
    texture=LoadTexture("assets/Bosses/IceBoss/IceBoss.png");
    state = std::make_unique<IBSeek>(*this);
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

    if (invulnerable) {
        invulnerableCounter++;
        if (invulnerableCounter >= 60) {
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
    //TODO: handle boss dmg
    //TODO: when two parts are broken, switch multiplier to aggressive
    health-=damage;
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


