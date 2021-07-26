
#include "ChasingBoss.h"
#include "iostream"

ChasingBoss::ChasingBoss(Vector2 position) : Object(ObjectTypes::other){
    currentPosition=position;
    targetPosition=position;
    texture = LoadTexture("assets/Bosses/FinalBoss/TEMP/EndbossIdle1.png");
}

void ChasingBoss::Update() {
    Vector2 moveTowardsPosition = {currentPosition.x - targetPosition.x,currentPosition.y - targetPosition.y};
    currentPosition = {currentPosition.x-(moveTowardsPosition.x/magnitude),currentPosition.y-(moveTowardsPosition.y/magnitude)};
}

void ChasingBoss::Draw() {
    DrawTexture(texture,(float)currentPosition.x,(float)currentPosition.y,WHITE);
}

void ChasingBoss::MovePosition(Vector2 newPosition) {
    targetPosition = newPosition;
}
