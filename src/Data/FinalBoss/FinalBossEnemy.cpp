//
// Created by Ashty on 26.07.2021.
//

#include "FinalBossEnemy.h"
#include "FBIdleFly.h"
#include <iostream>
#include "../../Global.h"

FinalBossEnemy::FinalBossEnemy(Vector2 location) : Enemy(EnemyTypes::Boss){
    texture = LoadTexture("assets/Bosses/FinalBoss/TEMP/EndbossIdle1.png");
    state = std::make_unique<FBIdleFly>();
    position = {94*32,73*32};
    bossPosition = location;

    sword = std::make_unique<BossSword>(location);
    health = 3;
}

void FinalBossEnemy::Update() {
    state=state->Update(*this);
    sword->Update();
    if (invulnerable) {
        invulnerableCounter++;
        if (invulnerableCounter >= 60) {
            invulnerableCounter = 0;
            invulnerable = false;
        }
    }
    moveTowardsPosition = {bossPosition.x - position.x,bossPosition.y - position.y};
    bossPosition = {bossPosition.x-(moveTowardsPosition.x/magnitude),bossPosition.y-(moveTowardsPosition.y/magnitude)};
    if(swordCounter <= 0) {
        sword->ChangeTarget(position);
    }else --swordCounter;
    hitbox = {bossPosition.x,bossPosition.y,(float)texture.width,(float)texture.height};
}

void FinalBossEnemy::Draw() {
    DrawTexture(texture,bossPosition.x,bossPosition.y,WHITE);
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

void FinalBossEnemy::ChangeSwordPosition(Vector2 newPos) {
    swordCounter = 90;
    sword->ChangeTarget(newPos);
}
