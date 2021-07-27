//
// Created by Ashty on 26.07.2021.
//

#include "FinalBossEnemy.h"
#include "FBIdleFly.h"
#include <iostream>

FinalBossEnemy::FinalBossEnemy(Vector2 location) : Enemy(EnemyTypes::Boss){
    texture = LoadTexture("assets/Bosses/FinalBoss/TEMP/EndbossIdle1.png");
    state = std::make_unique<FBIdleFly>();
    position = {94*32,73*32};
    bossPosition = location;
    sword = std::make_unique<BossSword>(location);
    health = 100;
}

void FinalBossEnemy::Update() {
    state=state->Update(*this);
    sword->Update();
    moveTowardsPosition = {bossPosition.x - position.x,bossPosition.y - position.y};
    bossPosition = {bossPosition.x-(moveTowardsPosition.x/magnitude),bossPosition.y-(moveTowardsPosition.y/magnitude)};
    sword->ChangeTarget(position);
    hitbox = {bossPosition.x,bossPosition.y,(float)texture.width,(float)texture.height};
}

void FinalBossEnemy::Draw() {
    DrawTexture(texture,bossPosition.x,bossPosition.y,WHITE);
    state->Draw(*this);
    sword->Draw();
}

void FinalBossEnemy::ReceiveDamage(int damage) {
    Enemy::ReceiveDamage(damage);
}

void FinalBossEnemy::ChangeTargetPosition(Vector2 newPos) {
    position = newPos;
}