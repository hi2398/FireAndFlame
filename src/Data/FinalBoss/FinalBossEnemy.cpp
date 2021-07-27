//
// Created by Ashty on 26.07.2021.
//

#include "FinalBossEnemy.h"
#include "FBIdleFly.h"

FinalBossEnemy::FinalBossEnemy(Vector2 location) : Enemy(EnemyTypes::Boss){
    texture = LoadTexture("assets/Bosses/FinalBoss/TEMP/EndbossIdle1.png");
    state = std::make_unique<FBIdleFly>();
    position = {94*32,73*32};
    bossPosition = location;
}

void FinalBossEnemy::Update() {
    state=state->Update(*this);
    moveTowardsPosition = {bossPosition.x - position.x,bossPosition.y - position.y};
    bossPosition = {bossPosition.x-(moveTowardsPosition.x/magnitude),bossPosition.y-(moveTowardsPosition.y/magnitude)};
}

void FinalBossEnemy::Draw() {
    DrawTexture(texture,bossPosition.x,bossPosition.y,WHITE);
    state->Draw(*this);
}

void FinalBossEnemy::ReceiveDamage(int damage) {
    Enemy::ReceiveDamage(damage);
}

void FinalBossEnemy::ChangeTargetPosition(Vector2 newPos) {
    position = newPos;
}