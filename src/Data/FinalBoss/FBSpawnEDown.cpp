//
// Created by Ashty on 26.07.2021.
//

#include "FBSpawnEDown.h"
#include "../../Global.h"
#include "../../Data/Enemies/Miner.h" // TODO replace with saugi
#include "FBIdleDown.h"

FBSpawnEDown::FBSpawnEDown() {
    Vector2 tempVec = {89*32,60*32};
    sceneManager->AddEnemy(std::make_unique<Miner>(tempVec));
    tempVec = {92*32,60*32};
    sceneManager->AddEnemy(std::make_unique<Miner>(tempVec));
    tempVec = {98*32,60*32};
    sceneManager->AddEnemy(std::make_unique<Miner>(tempVec));
    tempVec = {101*32,60*32};
    sceneManager->AddEnemy(std::make_unique<Miner>(tempVec));
}

std::shared_ptr<State> FBSpawnEDown::Update(Actor &actor) {
    if(waitCounter <= 0){
        return std::make_shared<FBIdleDown>();
    }
    --waitCounter;
    return shared_from_this();
}

void FBSpawnEDown::Draw(Actor &actor) {

}
