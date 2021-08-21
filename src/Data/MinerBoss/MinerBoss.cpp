#include "MinerBoss.h"
#include "MBPhaseTransitionState.h"
#include "../../Global.h"
#include "../SceneChangerObject.h"
#include "MBDecisionState.h"

MinerBoss::MinerBoss(Vector2 location) : Enemy(EnemyTypes::Boss) {
    SetPosition(location);
    health = maxHealth;
    debrisTexture = LoadTexture("assets/Bosses/MinerBoss/debris.png");
    texture = LoadTexture("assets/Bosses/MinerBoss/Miner.png");
    hitbox = {0, 0, 32, 32};
    hitbox.x = position.x;
    hitbox.y = position.y;
    movementSpeed = 3.f;

    state = std::make_unique<MBDecisionState>(*this);
}

void MinerBoss::Update() {
    hitbox.x=position.x;
    hitbox.y=position.y;
    state=state->Update(*this);

    --invulnerableCounter;
    if (invulnerableCounter<=0 && bossPhase!=MinerBossPhase::Transition) {
        invulnerable=false;
        invulnerableCounter=15;
    }
}

void MinerBoss::Draw() {
    state->Draw(*this);
}

void MinerBoss::ReceiveDamage(int damage) {
    health -= damage;
    invulnerable = true;
    invulnerableCounter=15;
    if (health <= 0)
    {
        markedDestroy= true;
        OnDeath();
    }
}

void MinerBoss::OnDeath() {
    std::cout << "Miner Boss Death\n";
    sceneManager->AddInteractable(std::make_unique<SceneChangerObject>(levelExit));
}

int MinerBoss::GetMaxHealth() const {
    return maxHealth;
}

MinerBossPhase MinerBoss::GetMinerBossPhase() const {
    return bossPhase;
}

void MinerBoss::SetMinerBossPhase(MinerBossPhase bossPhase) {
    this->bossPhase=bossPhase;
}
