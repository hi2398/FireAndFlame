//
// Created by Ashty on 26.07.2021.
//

#include "FBSpearAtk.h"
#include "../../Global.h"
#include "SpearAttack.h"
#include "FBIdleFly.h"

std::shared_ptr<State> FBSpearAtk::Update(Actor &actor) {
    --attackCounter;
    if(attackCounter <= 0 && !secondAttack){
        Vector2 tempVec = {89*32,73*32};
        sceneManager->AddInteractable(std::make_unique<SpearAttack>(tempVec));
        tempVec = {101*32,73*32};
        sceneManager->AddInteractable(std::make_unique<SpearAttack>(tempVec));
        tempVec = {92*32,75*32};
        sceneManager->AddInteractable(std::make_unique<SpearAttack>(tempVec));
        tempVec = {98*32,75*32};
        sceneManager->AddInteractable(std::make_unique<SpearAttack>(tempVec));
        secondAttack = true;
    }
    if(attackCounter <= -120){
        return std::make_shared<FBIdleFly>();
    }
    return shared_from_this();;
}

void FBSpearAtk::Draw(Actor &actor) {

}

FBSpearAtk::FBSpearAtk() {
    Vector2 tempVec = {89*32,73*32};
    sceneManager->AddInteractable(std::make_unique<SpearAttack>(tempVec));
    tempVec = {101*32,73*32};
    sceneManager->AddInteractable(std::make_unique<SpearAttack>(tempVec));
    tempVec = {92*32,71*32};
    sceneManager->AddInteractable(std::make_unique<SpearAttack>(tempVec));
    tempVec = {98*32,71*32};
    sceneManager->AddInteractable(std::make_unique<SpearAttack>(tempVec));
}