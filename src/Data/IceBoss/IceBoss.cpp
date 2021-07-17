#include "IceBoss.h"
#include "raymath.h"
#include "../../Global.h"
#include "IBSeek.h"

const float* IceBoss::multiplier;

IceBoss::IceBoss(Vector2 location) : Enemy(EnemyTypes::Boss) {
    SetPosition(location);
    texture=LoadTexture("assets/Bosses/IceBoss/IceBoss.png");
    parts.emplace_back(Part{-8, -8, 1, LoadTexture("assets/Bosses/IceBoss/Part.png"), 7});
    parts.emplace_back(Part{24, -8, 1, LoadTexture("assets/Bosses/IceBoss/Part.png"), 7});
    parts.emplace_back(Part{ -8, 24, 1, LoadTexture("assets/Bosses/IceBoss/Part.png"), 7});
    state = std::make_unique<IBSeek>();
    IceBoss::multiplier=&normalMultiplier; //set multiplier to point to the normal multiplier until boss goes into aggressive mode
}

void IceBoss::Update() {

    //states needed: part breaking, melee attack, ranged attack, pause(spawn minions+throw three barrels), seek player
    //all actions need an speed multiplier for aggression
    state=state->Update(*this);
}

void IceBoss::Draw() {

    //draw boss itself
    DrawTexture(texture, static_cast<int>(position.x), static_cast<int>(position.y), WHITE);

    //draw boss parts
    for (const auto& part : parts) {
        DrawTextureEx(part.texture, Vector2Add(position, part.offset), part.rotation, 1, WHITE);
    }
}

void IceBoss::ReceiveDamage(int damage) {
    //TODO: handle boss dmg
    //TODO: when two parts are broken, switch multiplier to aggressive
}

bool IceBoss::Decide() {
        static const int shift = static_cast<int>(std::log2(RAND_MAX));
        return (rand() >> shift) & 1;
}

float IceBoss::SpeedMultiplier() {
    return *multiplier;
}

float IceBoss::GetMeleeRange() {
    return meleeRange;
}

float IceBoss::GetRangedMinDistance() {
    return rangedMinDistance;
}

float IceBoss::GetMovementSpeed() {
    return movementSpeed;
}

