//
// Created by Ashty on 26.07.2021.
//

#include "FBSpawnE.h"
#include "FBIdleFly.h"
#include "../../Global.h"
#include "../../Data/Enemies/Miner.h" // TODO replace with saugi

FBSpawnE::FBSpawnE() {
    Vector2 tempVec = {89*32,60*32};
    sceneManager->AddEnemy(std::make_unique<Miner>(tempVec, EnemyLevel::Low));
    tempVec = {92*32,60*32};
    sceneManager->AddEnemy(std::make_unique<Miner>(tempVec, EnemyLevel::Low));
    tempVec = {98*32,60*32};
    sceneManager->AddEnemy(std::make_unique<Miner>(tempVec, EnemyLevel::Low));
    tempVec = {101*32,60*32};
    sceneManager->AddEnemy(std::make_unique<Miner>(tempVec, EnemyLevel::Low));

    bossSpeech = LoadSound("assets/audio/sfx/maraap_speech2.wav");
    PlaySound(bossSpeech);
}

std::shared_ptr<State> FBSpawnE::Update(Actor &actor) {
    --waitCounter;
    if(waitCounter <= 0){
        return std::make_shared<FBIdleFly>();
    }
    return shared_from_this();;
}

void FBSpawnE::Draw(Actor &actor) {

}