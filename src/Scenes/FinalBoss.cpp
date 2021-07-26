//
// Created by Ashty on 22.07.2021.
//

#include "FinalBoss.h"
#include "../Global.h"
#include "../Data/Coal.h"

FinalBoss::FinalBoss() {
    playerCharacter->SetPosition(playerStart);
    playerCharacter->active = true;
    playerCharacter->SetHealth(100);
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Placehalter_2.json","assets/Tilemaps/Testmap/finalBossScene.json");
    Vector2 tempVec = {14*32,78*32};

    chasingBossPositions[0] = {19*32,70*32, 16,16};
    chasingBossPositions[1] = {28*32,67*32, 16,16};
    chasingBossPositions[2] = {36*32,64*32, 16,16};
    chasingBossPositions[3] = {38*32,54*32, 16,16};
    chasingBossPositions[4] = {50*32,49*32, 16,16};
    chasingBossPositions[5] = {63*32,56*32, 16,16};
    chasingBossPositions[6] = {77*32,50*32, 16,16};
    chasingBossPositions[7] = {84*32,30*32, 16,16};

    playerCollidersForBossMovement[0] = {25*32,70*32, 32,256};
    playerCollidersForBossMovement[1] = {34*32,64*32, 32,500};
    playerCollidersForBossMovement[2] = {50*32,58*32, 32,600};
    playerCollidersForBossMovement[3] = {53*32,50*32, 32,256};
    playerCollidersForBossMovement[4] = {60*32,66*32, 32,256};
    playerCollidersForBossMovement[5] = {67*32,56*32, 32,256};

    tempVec = {31*32,60*32};
    interactables.emplace_back(std::make_unique<Coal>(tempVec));
    tempVec = {50*32,50*32};
    interactables.emplace_back(std::make_unique<Coal>(tempVec));
    tempVec = {70*32,50*32};
    interactables.emplace_back(std::make_unique<Coal>(tempVec));

    tempVec = {playerCharacter->GetPosition().x,playerCharacter->GetPosition().y-550};
    chasingBoss = std::make_unique<ChasingBoss>(tempVec);

    for(int i = 0; i<18; i++){
        bossFightBorder[i] = {(float)(86*32)+(32*i),57*32, 32, 32};
    }
}

void FinalBoss::Update() {
    Scene::Update();
    chasingBoss->Update();
    if(CheckCollisionRecs(platformerSequenceCollider,playerCharacter->playerHitbox)&&!isPlatformSequenceActive){
        isPlatformSequenceActive = true;
        chasingBoss->MovePosition({chasingBossPositions[0].x,chasingBossPositions[0].y});
    }
    if(CheckCollisionRecs(disablePlatformerSequenceCollider,playerCharacter->playerHitbox)&&isPlatformSequenceActive){
        chasingBoss->MovePosition({chasingBossPositions[7].x,chasingBossPositions[7].y});
        isPlatformSequenceActive = false;
        playerCharacter->SetHealth(100);
    }
    if(CheckCollisionRecs(bossFightSequenceCollider,playerCharacter->playerHitbox)){
        isBossFightSequenceActive = true;
        ActivateBorder();
    }
    if(CheckCollisionRecs(playerCollidersForBossMovement[0],playerCharacter->playerHitbox)){
        chasingBoss->MovePosition({chasingBossPositions[1].x,chasingBossPositions[1].y});
    }
    if(CheckCollisionRecs(playerCollidersForBossMovement[1],playerCharacter->playerHitbox)){
        chasingBoss->MovePosition({chasingBossPositions[2].x,chasingBossPositions[2].y});
    }
    if(CheckCollisionRecs(playerCollidersForBossMovement[2],playerCharacter->playerHitbox)){
        chasingBoss->MovePosition({chasingBossPositions[3].x,chasingBossPositions[3].y});
    }
    if(CheckCollisionRecs(playerCollidersForBossMovement[3],playerCharacter->playerHitbox)){
        chasingBoss->MovePosition({chasingBossPositions[4].x,chasingBossPositions[4].y});
    }
    if(CheckCollisionRecs(playerCollidersForBossMovement[4],playerCharacter->playerHitbox)){
        chasingBoss->MovePosition({chasingBossPositions[5].x,chasingBossPositions[5].y});
    }
    if(CheckCollisionRecs(playerCollidersForBossMovement[5],playerCharacter->playerHitbox)){
        chasingBoss->MovePosition({chasingBossPositions[6].x,chasingBossPositions[6].y});
    }
    if(isPlatformSequenceActive) {
        UpdatePlatformSequence();
    }
}

void FinalBoss::Draw() {
    Scene::Draw();
    chasingBoss->Draw();
}

void FinalBoss::UpdatePlatformSequence() {
    ++timerForSpearRespawn;
    if(timerForSpearRespawn == 60){
        Vector2 tempVec = {playerCharacter->GetPosition().x + GetRandomValue(-128,128),playerCharacter->GetPosition().y + GetRandomValue(128,190)};
        interactables.emplace_back(std::make_unique<SpearAttack>(tempVec));
    }
    if(timerForSpearRespawn >= 120){
        timerForSpearRespawn = 0;
        Vector2 tempVec = {playerCharacter->GetPosition().x + GetRandomValue(-128,128),playerCharacter->GetPosition().y - GetRandomValue(96,120)};
        interactables.emplace_back(std::make_unique<SpearAttack>(tempVec));
    }
}

void FinalBoss::UpdateBossFightSequence() {

}

void FinalBoss::ActivateBorder() {
    for(int i = 0; i<18; i++){
        Vector2 tempVec = {bossFightBorder[i].x,bossFightBorder[i].y};
        tilemap->AddCollisionTile(tempVec);
    }
}
