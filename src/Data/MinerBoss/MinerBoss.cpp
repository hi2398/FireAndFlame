#include "MinerBoss.h"
#include "MBPhaseTransitionState.h"
#include "../../Global.h"
#include "../SceneChangerObject.h"
#include "../../Scenes/MinerBossScene.h"
#include "MBBeforeFight.h"
#include "raymath.h"

MinerBoss::MinerBoss(Vector2 location) : Enemy(EnemyTypes::Boss) {
    SetPosition(location);
    health = maxHealth;
    debrisTexture = LoadTexture("assets/Bosses/MinerBoss/debris.png");
    texture = LoadTexture("assets/Bosses/MinerBoss/Miner_Boss_Spritesheet.png");
    state = std::make_unique<MBBeforeFight>(*this);
    hitbox = {0, 0, 32, 32};
    hitbox.x = position.x;
    hitbox.y = position.y;
    movementSpeed = 3.f;
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

    hud->SetBossEnemyHealth(health, 7.5);
    if (enableDebris){
        if (debrisTimer>0){
            --debrisTimer;
            debrisDrawLoc=Vector2Lerp(debrisStartLoc, debrisEndLoc, 1.f-debrisTimer/100.f);

            if (debrisTimer==0){
                sceneManager->GetTilemap()->AddCollisionTile(debrisEndLoc);
                std::shared_ptr <MinerBossScene> scene= std::dynamic_pointer_cast<MinerBossScene>(sceneManager->GetActiveScene());
                scene->EnableDebrisLower();
                enableDebris = false;
            }
        }
    }

    if (!phase2debrisEnabled) {
        if (playerCharacter->GetPosition().y<=(59*32)){
            std::shared_ptr <MinerBossScene> scene= std::dynamic_pointer_cast<MinerBossScene>(sceneManager->GetActiveScene());
            scene->EnableDebrisUpper();
            phase2debrisEnabled= true;
        }
    }
}

void MinerBoss::Draw() {
    state->Draw(*this);
    if (enableDebris){
        DrawTextureV(debrisTexture, debrisDrawLoc, WHITE);
    }
}

void MinerBoss::ReceiveDamage(int damage) {
    if  (bossPhase==MinerBossPhase::Transition){
        return;
    }
    health -= damage;
    invulnerable = true;
    invulnerableCounter=15;
    if (health <= 0)
    {
        markedDestroy= true;
        OnDeath();
    }
}

void MinerBoss::UnloadUsedTextures()
{
    UnloadTexture(texture);
    UnloadTexture(debrisTexture);
}

MinerBoss::~MinerBoss()
{

}

void MinerBoss::OnDeath() {
    sceneManager->AddInteractable(std::make_unique<SceneChangerObject>(levelExit, SceneEnums::NeutralArea ,SceneEnums::MinerBoss));
    UnloadUsedTextures();
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

void MinerBoss::EnableDebris() {
    enableDebris=true;
}
