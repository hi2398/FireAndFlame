#include "IceBoss.h"
#include "raymath.h"

IceBoss::IceBoss(Vector2 location) : Enemy(EnemyTypes::Boss) {
    SetPosition(location);
    texture=LoadTexture("assets/Bosses/IceBoss/IceBoss.png");
    parts.emplace_back(Part{-8, -8, 1, LoadTexture("assets/Bosses/IceBoss/Part.png"), 7});
    parts.emplace_back(Part{24, -8, 1, LoadTexture("assets/Bosses/IceBoss/Part.png"), 7});
    parts.emplace_back(Part{ -8, 24, 1, LoadTexture("assets/Bosses/IceBoss/Part.png"), 7});
}

void IceBoss::Update() {

    //states needed: part breaking, melee attack, ranged attack, pause(spawn minions+throw three barrels),
    //all actions need an speed multiplier for aggression

}

void IceBoss::Draw() {
    Vector2 playerPos=GetPosition();

    //draw boss itself
    DrawTexture(texture, static_cast<int>(playerPos.x), static_cast<int>(playerPos.y), WHITE);

    //draw boss parts
    for (const auto& part : parts) {
        DrawTextureEx(part.texture, Vector2Add(playerPos, part.offset), part.rotation, 1, WHITE);
    }
}

void IceBoss::ReceiveDamage(int damage) {
    //TODO: handle boss dmg
}

