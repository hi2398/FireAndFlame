//
// Created by Ashty on 26.07.2021.
//

#include "FinalBossEnemy.h"
#include "FBIdleFly.h"
#include <iostream>
#include "../../Global.h"

FinalBossEnemy::FinalBossEnemy(Vector2 location) : Enemy(EnemyTypes::Boss){
    state = std::make_unique<FBIdleFly>();
    position = {96*32,73*32};
    bossPosition = location;

    sword = std::make_unique<BossSword>(location);
    health = 75;
}

void FinalBossEnemy::Update() {
    state=state->Update(*this);
    sword->Update();
    hud->SetBossEnemyHealth(health, 4);
    if (invulnerable) {
        invulnerableCounter++;
        if (invulnerableCounter >= 30) {
            invulnerableCounter = 0;
            invulnerable = false;
        }
    }
    moveTowardsPosition = {bossPosition.x - position.x,bossPosition.y - position.y};
    bossPosition = {bossPosition.x-(moveTowardsPosition.x/magnitude),bossPosition.y-(moveTowardsPosition.y/magnitude)};
    if(swordCounter <= 0) {
        sword->ChangeTarget(position);
    }else --swordCounter;
    hitbox = {bossPosition.x+6,bossPosition.y+6,52,52};
}

void FinalBossEnemy::Draw() {
    state->Draw(*this);
    sword->Draw();
}

void FinalBossEnemy::ReceiveDamage(int damage) {
    health -= damage;
    if(health <= 0){
        sceneManager->RemoveAllInteractables();
        playerCharacter->SetHealth(100);
    }
}

void FinalBossEnemy::ChangeTargetPosition(Vector2 newPos) {
    position = newPos;
}

int FinalBossEnemy::GetHealth() {
    return health;
}

FinalBossEnemy::~FinalBossEnemy()
{
    UnloadTexture(texture);
}

void FinalBossEnemy::ChangeSwordPosition(Vector2 newPos) {
    swordCounter = 90;
    sword->ChangeTarget(newPos);
}

Vector2 FinalBossEnemy::GetPositionFix() {
    Vector2 bossPos = {hitbox.x, hitbox.y};
    return bossPos;
}