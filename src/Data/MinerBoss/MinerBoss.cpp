#include "MinerBoss.h"
#include "MBPhaseTransitionState.h"
#include "../../Global.h"
#include "../SceneChangerObject.h"

MinerBoss::MinerBoss(Vector2 location) : Enemy(EnemyTypes::Boss) {
    SetPosition(location);
    texture= LoadTexture("assets/Bosses/MinerBoss/Miner.png");
    state=std::make_unique<MBPhaseTransitionState>();
}

void MinerBoss::Update() {
    state=state->Update(*this);
}

void MinerBoss::Draw() {
    state->Draw(*this);
}

void MinerBoss::ReceiveDamage(int damage) {
    Enemy::ReceiveDamage(damage);
    if (health==0) {
        OnDeath();
    }
}

void MinerBoss::OnDeath() {
    sceneManager->AddInteractable(std::make_unique<SceneChangerObject>(levelExit));
}
