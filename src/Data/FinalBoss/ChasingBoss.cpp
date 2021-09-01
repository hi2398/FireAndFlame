
#include "ChasingBoss.h"
#include "iostream"

ChasingBoss::ChasingBoss(Vector2 position) : Object(ObjectTypes::other){
    currentPosition=position;
    targetPosition=position;
    activeFrame = {0,0,64,64};
    texture = LoadTexture("assets/Bosses/FinalBoss/MaraapSprites.png");
}

void ChasingBoss::Update() {
    Vector2 moveTowardsPosition = {currentPosition.x - targetPosition.x,currentPosition.y - targetPosition.y};
    currentPosition = {currentPosition.x-(moveTowardsPosition.x/magnitude),currentPosition.y-(moveTowardsPosition.y/magnitude)};
    if(counter == 0){
        counter = 40;
        switch ((int)activeFrame.x) {
            case 0: activeFrame = {64,0,64,64};
                break;
            case 32: activeFrame = {128,0,64,64};
                break;
            case 64: activeFrame = {0,0,64,64};
                break;
            default:
                break;

        }
    }else {counter--;}
}

void ChasingBoss::Draw() {
    DrawTextureRec(texture,activeFrame,currentPosition,WHITE);
}

void ChasingBoss::MovePosition(Vector2 newPosition) {
    targetPosition = newPosition;
}
