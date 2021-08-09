#include "MinerBoss.h"
#include "MBPhaseTransitionState.h"
#include "../../Global.h"
#include "../SceneChangerObject.h"

MinerBoss::MinerBoss(Vector2 location) : Enemy(EnemyTypes::Boss) {
    SetPosition(location);
    health=40;
    texture= LoadTexture("assets/Bosses/MinerBoss/Miner.png");
    state=std::make_unique<MBPhaseTransitionState>();
    hitbox={0, 0, 32, 32};
    hitbox.x=position.x;
    hitbox.y=position.y;
}

void MinerBoss::Update() {
    hitbox.x=position.x;
    hitbox.y=position.y;
    state=state->Update(*this);

    --invulnerableCounter;
    if (invulnerableCounter<=0) {
        invulnerable=false;
        invulnerableCounter=15;
    }
    std::cout << invulnerable;
}

void MinerBoss::Draw() {
    state->Draw(*this);
    DrawRectangleRec(hitbox, RED);
}

void MinerBoss::ReceiveDamage(int damage) {
    health -= damage;
    if (health <= 0)
    {
        markedDestroy= true;
        OnDeath();
    }
}

void MinerBoss::OnDeath() {
    sceneManager->AddInteractable(std::make_unique<SceneChangerObject>(levelExit));
}
