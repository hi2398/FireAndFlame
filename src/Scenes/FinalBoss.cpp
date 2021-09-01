//
// Created by Ashty on 22.07.2021.
//

#include "FinalBoss.h"
#include "../Global.h"
#include "../Data/Coal.h"
#include "../Data/FinalBoss/FinalBossEnemy.h"
#include "../Data/FinalBoss/BossEnergySwordAttack.h"
#include "../Data/Deathzone.h"


FinalBoss::FinalBoss(SceneEnums lastScene) : Scene(SceneEnums::FinalBoss) {
    this->lastScene = lastScene;
    playerCharacter->SetPosition(playerStart);
    playerCharacter->active = true;
    playerCharacter->SetHealth(100);
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/overworldTileset.json","assets/Tilemaps/Final_Boss_Tilemap.json");
    Vector2 tempVec = {14*32,78*32};

    chasingBossPositions[0] = {19*32,70*32, 16,16};
    chasingBossPositions[1] = {28*32,67*32, 16,16};
    chasingBossPositions[2] = {36*32,64*32, 16,16};
    chasingBossPositions[3] = {38*32,54*32, 16,16};
    chasingBossPositions[4] = {50*32,49*32, 16,16};
    chasingBossPositions[5] = {63*32,56*32, 16,16};
    chasingBossPositions[6] = {77*32,50*32, 16,16};
    chasingBossPositions[7] = {105*32,45*32, 16,16};

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
    tempVec = {playerCharacter->GetPosition().x-16,playerCharacter->GetPosition().y-550};
    sword = std::make_unique<BossSword>(tempVec);

    tempVec = {-200, 130*32};
    interactables.emplace_back(std::make_unique<Deathzone>(tempVec));

    for(int i = 0; i<18; i++){
        bossFightBorder[i] = {(float)(86*32)+(32*i),57*32, 32, 32};
    }

    //background initialization
    textureForegroundException = LoadTexture("assets/graphics/backgrounds/Surface/surface_fore_ex.png");
    textureForegroundMain = LoadTexture("assets/graphics/backgrounds/Surface/surface_fore.png");
    textureBackgroundMain = LoadTexture("assets/graphics/backgrounds/Surface/surface_back.png");
    textureBackgroundException = LoadTexture("assets/graphics/backgrounds/Surface/surface_back_ex.png");

    foregroundPos = { 0,2230 };
    backgroundPos = { 0,2350 };
    backgroundMultiplier = 1.3f;

    //fill background loop vector
    backgroundLoopX = 10;
    backgroundLoopY = 2;
    backgroundException = 1;

    foregroundLoopX = 5;
    foregroundLoopY = 2;
    foregroundException = 1;

    //example for weathereffect
    sceneEffectActivated = true;
    sceneEffect = LoadTexture("assets/graphics/backgrounds/AreaThree/ash.png");
    effectPos1Start = { 0,1100 };
    effectPos2Start = { 500,1100 - 400 * 4 };
    effectPos1 = effectPos1Start;
    effectPos2 = effectPos2Start;
}

void FinalBoss::Update() {
    Scene::Update();
    chasingBoss->Update();
    sword->Update();
    if(CheckCollisionRecs(platformerSequenceCollider,playerCharacter->playerHitbox)&&!isPlatformSequenceActive){
        isPlatformSequenceActive = true;
        sceneManager->ScreenShake(20);
        chasingBoss->MovePosition({chasingBossPositions[0].x,chasingBossPositions[0].y});
        sword->ChangeTarget({chasingBossPositions[0].x-16,chasingBossPositions[0].y});
    }
    if(CheckCollisionRecs(disablePlatformerSequenceCollider,playerCharacter->playerHitbox)&&isPlatformSequenceActive){
        chasingBoss->MovePosition({chasingBossPositions[7].x,chasingBossPositions[7].y});
        sword->ChangeTarget({chasingBossPositions[7].x-16,chasingBossPositions[7].y});
        isPlatformSequenceActive = false;
        playerCharacter->SetHealth(100);
    }
    if(CheckCollisionRecs(bossFightSequenceCollider,playerCharacter->playerHitbox)&&!isBossFightSequenceActive){
        isBossFightSequenceActive = true;
        ActivateBorder();
    }
    if(CheckCollisionRecs(playerCollidersForBossMovement[0],playerCharacter->playerHitbox)){
        chasingBoss->MovePosition({chasingBossPositions[1].x,chasingBossPositions[1].y});
        sword->ChangeTarget({chasingBossPositions[1].x-16,chasingBossPositions[1].y});
    }
    if(CheckCollisionRecs(playerCollidersForBossMovement[1],playerCharacter->playerHitbox)){
        chasingBoss->MovePosition({chasingBossPositions[2].x,chasingBossPositions[2].y});
        sword->ChangeTarget({chasingBossPositions[2].x-16,chasingBossPositions[2].y});
    }
    if(CheckCollisionRecs(playerCollidersForBossMovement[2],playerCharacter->playerHitbox)){
        chasingBoss->MovePosition({chasingBossPositions[3].x,chasingBossPositions[3].y});
        sword->ChangeTarget({chasingBossPositions[3].x-16,chasingBossPositions[3].y});
    }
    if(CheckCollisionRecs(playerCollidersForBossMovement[3],playerCharacter->playerHitbox)){
        chasingBoss->MovePosition({chasingBossPositions[4].x,chasingBossPositions[4].y});
        sword->ChangeTarget({chasingBossPositions[4].x-16,chasingBossPositions[4].y});
    }
    if(CheckCollisionRecs(playerCollidersForBossMovement[4],playerCharacter->playerHitbox)){
        chasingBoss->MovePosition({chasingBossPositions[5].x,chasingBossPositions[5].y});
        sword->ChangeTarget({chasingBossPositions[5].x-16,chasingBossPositions[5].y});
    }
    if(CheckCollisionRecs(playerCollidersForBossMovement[5],playerCharacter->playerHitbox)){
        chasingBoss->MovePosition({chasingBossPositions[6].x,chasingBossPositions[6].y});
        sword->ChangeTarget({chasingBossPositions[6].x-16,chasingBossPositions[6].y});
    }
    if(isPlatformSequenceActive) {
        UpdatePlatformSequence();
    }
}

void FinalBoss::Draw() {
    Scene::Draw();
    chasingBoss->Draw();
    sword->Draw();
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
    Vector2 tempVec = {94*32,46*32};
    enemies.emplace_back(std::make_unique<FinalBossEnemy>(tempVec));
}