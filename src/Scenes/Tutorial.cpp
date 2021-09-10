#include "Tutorial.h"
#include "../Global.h"
#include "../Data/DialogueObject.h"
#include "../Data/NPC.h"
#include "../Data/SceneChangerObject.h"
#include "../Data/Enemies/Miner.h"
#include "../Data/Coal.h"
#include "../Data/Deathzone.h"
#include "../Data/SaveInteractable.h"

Tutorial::Tutorial(SceneEnums lastScene) : Scene(SceneEnums::Tutorial) {
    this->lastScene = lastScene;
    playerCharacter->SetPosition(playerStart);
    playerCharacter->active = true;
    playerCharacter->SetHealth(90);
    npc1Tex = LoadTexture("assets/graphics/NPCs/Npc1.png");
    npc2Tex = LoadTexture("assets/graphics/NPCs/Npc2.png");
    npc3Tex = LoadTexture("assets/graphics/NPCs/Npc3.png");
    npc4Tex = LoadTexture("assets/graphics/NPCs/Npc4.png");
    npc5Tex = LoadTexture("assets/graphics/NPCs/Npc5.png");
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Tilemap_1.json","assets/Tilemaps/Tutorial_Tilemap.json");

    Vector2 tempVec = {-200, 130*32};
    interactables.emplace_back(std::make_unique<Deathzone>(tempVec));

    interactables.emplace_back(std::make_unique<NPC>("assets/Dialogues/tutorialText1.json",npc1Pos,NPCType::one));
    interactables.emplace_back(std::make_unique<NPC>("assets/Dialogues/tutorialText2.json",npc2Pos,NPCType::two));
    interactables.emplace_back(std::make_unique<NPC>("assets/Dialogues/tutorialText3.json",npc3Pos,NPCType::three));
    interactables.emplace_back(std::make_unique<NPC>("assets/Dialogues/tutorialText4.json",npc4Pos,NPCType::four));//TODO Change Dialogue
    interactables.emplace_back(std::make_unique<NPC>("assets/Dialogues/tutorialText5.json",npc5Pos,NPCType::five));

    tempVec = {86*32,36*32};
    interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec,SceneEnums::IceBoss, sceneName));


    speech.emplace_back(std::make_unique<Speechbubble>(npc1Pos));
    speech.emplace_back(std::make_unique<Speechbubble>(npc2Pos));
    speech.emplace_back(std::make_unique<Speechbubble>(npc3Pos));
    speech.emplace_back(std::make_unique<Speechbubble>(npc4Pos));
    speech.emplace_back(std::make_unique<Speechbubble>(npc5Pos));

    tempVec = {87*32,39*32};
    tilemap->AddCollisionTile(tempVec);

    tempVec = {52*32,46*32};
    enemies.emplace_back(std::make_unique<Miner>(tempVec, EnemyLevel::Low));
    tempVec = {64*32,42*32};
    enemies.emplace_back(std::make_unique<Miner>(tempVec, EnemyLevel::Low));
    tempVec = {67*32,42*32};
    enemies.emplace_back(std::make_unique<Miner>(tempVec, EnemyLevel::Low));
    tempVec = {86*32,39*32};
    enemies.emplace_back(std::make_unique<Miner>(tempVec, EnemyLevel::Low));

    tempVec = { 53 * 32,77 * 32 };
    spawner.emplace_back(std::make_unique<Spawner>(tempVec, SpawnerDirection::Up ,SpawnerType::Coal));

    tempVec = {80*32,99*32+3};
    Texture2D statueTex = LoadTexture("assets/graphics/Sign.png");
    interactables.emplace_back(std::make_unique<DialogueObject>("assets/Dialogues/TutorialSign.json",tempVec,statueTex));

    door1[0] = {58*32,76*32};
    door1[1] = {58*32,75*32};

    door2[0] = {49*32,76*32};
    door2[1] = {49*32,75*32};

    door3[0] = {40*32,76*32};
    door3[1] = {40*32,75*32};

    textureForegroundException = LoadTexture("assets/graphics/backgrounds/Tutorial/crematorium_layer_01_bottom.png");
    textureForegroundMain = LoadTexture("assets/graphics/backgrounds/Tutorial/crematorium_layer_01_sides.png");
    textureBackgroundMain = LoadTexture("assets/graphics/backgrounds/Tutorial/crematorium_layer_02.png");
    textureBackgroundException = LoadTexture("assets/graphics/backgrounds/Tutorial/crematorium_layer_02.png");

    foregroundPos = { 0, - 90 };
    backgroundPos = { 0,0 };
    
    //fill background loop vector
    backgroundLoopX = 8;
    backgroundLoopY = 16;
    backgroundException = 0;

    foregroundLoopX = 4;
    foregroundLoopY = 8;
    foregroundException = 7;

    //checkpoints
    interactables.emplace_back(std::make_unique<SaveInteractable>(checkpointA));

    topDoor = LoadTexture("assets/graphics/TopDoor.png");
    downDoor = LoadTexture("assets/graphics/DownDoor.png");

    track = LoadMusicStream("assets/audio/tracks/Tutorial1.mp3");
    PlayMusicStream(track);

}

void Tutorial::Update() {
    if (preventHealthDecrease)UpdateMusicStream(track);
    else {
        if (static_cast<int>(GetMusicTimePlayed(track)) % 3 == 0) StopMusicStream(track);
    }
    Scene::Update();
    for (const auto& bubble : speech) {
		bubble->Update();
    }
    
    if(preventHealthDecrease){ // Manages if player loses health in Tutorial
        playerCharacter->SetPlayerDecreasingHealth(false);
    }else playerCharacter->SetPlayerDecreasingHealth(true);
    if(CheckCollisionRecs(playerCharacter->playerHitbox,healthDecreasingCollider)){
        preventHealthDecrease = false;
    }

    if(CheckCollisionRecs(playerCharacter->playerHitbox,tutorial1Trigger) && !tutorial1 && door1Active){
        tutorial1 = true;
        tilemap->AddCollisionTile(door1[0]);
        tilemap->AddCollisionTile(door1[1]);
    }
    if(CheckCollisionRecs(playerCharacter->playerHitbox,tutorial2Trigger) && !tutorial2 && door2Active){
        tutorial2 = true;
        tilemap->AddCollisionTile(door2[0]);
        tilemap->AddCollisionTile(door2[1]);
    }
    if(CheckCollisionRecs(playerCharacter->playerHitbox,tutorial3Trigger) && !tutorial3 && door3Active){
        tutorial3 = true;
        tilemap->AddCollisionTile(door3[0]);
        tilemap->AddCollisionTile(door3[1]);
    }

    if(tutorial1){ //TODO Rework required if Player controls change
        if(IsKeyPressed(KEY_ENTER) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)){
            ++attackCounter;
            --attackTicker;
            if(attackCounter >= 3){
                door1Active = false;
                tutorial1 = false;
                tilemap->RemoveCollisionTile();
                tilemap->RemoveCollisionTile();
            }
        }
        if(attackTicker != 123){
            --attackTicker;
        }
        if(attackTicker <= 0){
            attackTicker = 123;
            attackCounter = 0;
        }
    }
    if(tutorial2){
        if(playerCharacter->GetHealth() >= 99){
            door2Active = false;
            tutorial2 = false;
            tilemap->RemoveCollisionTile();
            tilemap->RemoveCollisionTile();
        }
    }
    if(tutorial3){
        if (IsKeyPressed(KEY_F) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)){
            door3Active = false;
            tutorial3 = false;
            tilemap->RemoveCollisionTile();
            tilemap->RemoveCollisionTile();
        }
    }

    for (const auto& spawn : spawner) {
        spawn->Update();
        if (spawn->GetType() == SpawnerType::Coal) {
            spawn->SpawnCoal();
        }
    }
}

void Tutorial::Draw() {
    if(door1Active){
        DrawTexture(topDoor,door1[0].x,door1[0].y-32,WHITE);
        DrawTexture(downDoor,door1[0].x,door1[0].y,WHITE);
    }if(door2Active){
        DrawTexture(topDoor,door2[0].x,door2[0].y-32,WHITE);
        DrawTexture(downDoor,door2[0].x,door2[0].y,WHITE);
    }
    if(door3Active){
        DrawTexture(topDoor,door3[0].x,door3[0].y-32,WHITE);
        DrawTexture(downDoor,door3[0].x,door3[0].y,WHITE);
    }


    for (const auto& spawn : spawner) {
        spawn->Draw();
    }

    for (const auto& bubble : speech) {
        bubble->Draw();
    }
}

Tutorial::~Tutorial() {
    UnloadMusicStream(track);
}