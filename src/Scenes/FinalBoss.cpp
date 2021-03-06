#include "FinalBoss.h"
//
// Created by Ashty on 22.07.2021.
//

#include "FinalBoss.h"
#include "../Global.h"
#include "../Data/Coal.h"
#include "../Data/FinalBoss/FinalBossEnemy.h"
#include "../Data/FinalBoss/BossEnergySwordAttack.h"
#include "../Data/Deathzone.h"
#include "../Data/DialogueObject.h"
#include "../Data/SaveInteractable.h"


FinalBoss::FinalBoss(SceneEnums lastScene) : Scene(SceneEnums::FinalBoss) {
    this->lastScene = lastScene;
    playerCharacter->SetPosition(playerStart);
    playerCharacter->active = true;
    playerCharacter->SetHealth(100);
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/overworldTileset.json","assets/Tilemaps/Final_Boss_Tilemap.json");
    Vector2 tempVec = {7*32,66*32};
    for (int i = 0; i < 9; i++) {
        tilemap->AddCollisionTile(tempVec);
        tempVec.x += 32;
    }

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

    tempVec = {31*32,74*32};
    spawner.emplace_back(std::make_unique<Spawner>(tempVec, SpawnerDirection::Up, SpawnerType::Coal));
    tempVec = {54*32,51*32};
    spawner.emplace_back(std::make_unique<Spawner>(tempVec, SpawnerDirection::Down, SpawnerType::Coal));
    tempVec = {70*32,54*32};
    spawner.emplace_back(std::make_unique<Spawner>(tempVec, SpawnerDirection::Down, SpawnerType::Coal));
    tempVec = {104*32, 71*32};
    spawner.emplace_back(std::make_unique<Spawner>(tempVec, SpawnerDirection::Left, SpawnerType::Coal));
    tempVec = { 85 * 32, 71 * 32 };
    spawner.emplace_back(std::make_unique<Spawner>(tempVec, SpawnerDirection::Right, SpawnerType::Coal));

    tempVec = {playerCharacter->GetPosition().x,playerCharacter->GetPosition().y-550};
    chasingBoss = std::make_unique<ChasingBoss>(tempVec);
    tempVec = {playerCharacter->GetPosition().x-16,playerCharacter->GetPosition().y-550};
    sword = std::make_unique<BossSword>(tempVec);

    tempVec = {-200, 130*32};
    interactables.emplace_back(std::make_unique<Deathzone>(tempVec));

    for(int i = 0; i<18; i++){
        bossFightBorder[i] = {(float)(86*32)+(32*i),57*32, 32, 32};
    }

    tempVec = {14*32,82*32+3};
    statueTex = LoadTexture("assets/graphics/Sign.png");
    interactables.emplace_back(std::make_unique<DialogueObject>("assets/Dialogues/Final_BossSign.json",tempVec,statueTex));

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


    intro = LoadMusicStream("assets/audio/tracks/FinalBossIntro.mp3");
    loop = LoadMusicStream("assets/audio/tracks/FinalBossLoop1.mp3");
    fight = LoadMusicStream("assets/audio/tracks/FinalBoss_FightIntro.mp3");
    fightLoop = LoadMusicStream("assets/audio/tracks/FinalBoss_FightLoop.mp3");

    SetMusicVolume(intro, soundManager->GetTrackVolume());
    SetMusicVolume(loop, soundManager->GetTrackVolume());
    SetMusicVolume(fight, soundManager->GetTrackVolume());
    SetMusicVolume(fightLoop, soundManager->GetTrackVolume());

    intro.looping = false;
    //checkpoints
    interactables.emplace_back(std::make_unique<SaveInteractable>(checkpointA));

    playerCharacter->SetUnlockedAbilityLevel(AbilitiesUnlocked::Doublejump);
}

void FinalBoss::Update() {
    Scene::Update();
    chasingBoss->Update();
    sword->Update();
    for (const auto& spawn : spawner) {
        spawn->Update();
        if (spawn->GetType() == SpawnerType::Coal) {
            spawn->SpawnCoal();
        }
    }
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
        hud->IsBossFightActive(true);
        sceneManager->ScreenShake(30);
        ActivateBorder();
        if (loopPlaying = true) {
            StopMusicStream(loop);
        }
        else {
            StopMusicStream(intro);
        }
        PlayMusicStream(fight);
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
		if (!introPlaying)PlayMusicStream(intro), introPlaying = true;
        
    }
	if (introPlaying && !loopPlaying && !isBossFightSequenceActive) {
		UpdateMusicStream(intro);
		introCounter++;
	}
	if ((introCounter >= 1690 && !loopPlaying)) {
		StopMusicStream(intro);
		PlayMusicStream(loop);
		loopPlaying = true;
	}
    if (loopPlaying && !secondLoopPlaying && !isBossFightSequenceActive) {
        UpdateMusicStream(loop);
        
    }
    if (isBossFightSequenceActive) {
        if (GetMusicTimePlayed(fight)>= 53.1 && !secondLoopPlaying) {
            skipFrame++;
        }
        if (skipFrame == 5) {
			StopMusicStream(fight);
			secondLoopPlaying = true;
			PlayMusicStream(fightLoop);
        }
        if (!musicActivated) {
			if (!secondLoopPlaying) UpdateMusicStream(fight);
			else if (secondLoopPlaying)UpdateMusicStream(fightLoop);
        }
    }
}

void FinalBoss::Draw() {
    Scene::Draw();
    chasingBoss->Draw();
    sword->Draw();
    for (const auto& spawnCoal : spawner) {
        spawnCoal->Draw();
    }
}

void FinalBoss::UpdatePlatformSequence() {
    ++timerForSpearRespawn;
    if(timerForSpearRespawn == 25){
        Vector2 tempVec = {playerCharacter->GetPosition().x + GetRandomValue(-128,128),playerCharacter->GetPosition().y + GetRandomValue(128,190)};
        interactables.emplace_back(std::make_unique<SpearAttack>(tempVec));
    }
    if(timerForSpearRespawn >= 50){
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

FinalBoss::~FinalBoss()
{
    UnloadTexture(sceneEffect);
    UnloadTexture(textureBackgroundException);
    UnloadTexture(textureBackgroundMain);
    UnloadTexture(textureForegroundException);
    UnloadTexture(textureForegroundMain);
    UnloadTexture(statueTex);

    UnloadMusicStream(intro);
    UnloadMusicStream(loop);
    UnloadMusicStream(fight);
    UnloadMusicStream(fightLoop);
}
