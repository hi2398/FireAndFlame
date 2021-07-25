//
// Created by Ashty on 22.07.2021.
//

#include "FinalBoss.h"
#include "../Global.h"

FinalBoss::FinalBoss() {
    playerCharacter->SetPosition(playerStart);
    playerCharacter->active = true;
    playerCharacter->SetHealth(90);
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Placehalter_2.json","assets/Tilemaps/Testmap/finalBossScene.json");
    Vector2 tempVec = {14*32,78*32};
    debugRecs.push_back({tempVec.x,tempVec.y,32*5,32});
    debugRecs.push_back({80*32,46*32, 32, 360});
    debugRecs.push_back({86*32,61*32, 576, 32});
    for(int i = 0; i<18; i++){
        bossFightBorder[i] = {(float)(86*32)+(32*i),57*32, 32, 32};
        debugRecs.push_back(bossFightBorder[i]);
    }
}

void FinalBoss::Update() {
    Scene::Update();
    if(CheckCollisionRecs(platformerSequenceCollider,playerCharacter->playerHitbox)&&!isPlatformSequenceActive){
        isPlatformSequenceActive = true;
    }
    if(CheckCollisionRecs(disablePlatformerSequenceCollider,playerCharacter->playerHitbox)&&isPlatformSequenceActive){
        isPlatformSequenceActive = false;
    }
    if(CheckCollisionRecs(bossFightSequenceCollider,playerCharacter->playerHitbox)){
        isBossFightSequenceActive = true;
        ActivateBorder();
    }
    if(isPlatformSequenceActive) {
        UpdatePlatformSequence();
    }
}

void FinalBoss::Draw() {
    Scene::Draw();
    for(const auto& x : debugRecs){
        DrawRectangleRec(x,WHITE);
    }
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
