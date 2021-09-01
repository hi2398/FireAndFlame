#include "Tutorial.h"
#include "../Global.h"
#include "../Data/DialogueObject.h"
#include "../Data/SceneChangerObject.h"
#include "../Data/Enemies/Miner.h"
#include "../Data/Coal.h"
#include "../Data/Deathzone.h"

Tutorial::Tutorial(SceneEnums lastScene) : Scene(SceneEnums::TraitorBoss) {
    this->lastScene = lastScene;
    playerCharacter->SetPosition(playerStart);
    playerCharacter->active = true;
    playerCharacter->SetHealth(90);
    npc1Tex = LoadTexture("assets/graphics/PLAYER.png"); // TODO change NPC Texture
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Tilemap_1.json","assets/Tilemaps/Tutorial_Tilemap.json");

    Vector2 tempVec = {-200, 130*32};
    interactables.emplace_back(std::make_unique<Deathzone>(tempVec));

    interactables.emplace_back(std::make_unique<DialogueObject>("assets/Dialogues/tutorialText1.json",npc1Pos,npc1Tex));
    interactables.emplace_back(std::make_unique<DialogueObject>("assets/Dialogues/tutorialText2.json",npc2Pos,npc1Tex));
    interactables.emplace_back(std::make_unique<DialogueObject>("assets/Dialogues/tutorialText3.json",npc3Pos,npc1Tex));
    interactables.emplace_back(std::make_unique<DialogueObject>("assets/Dialogues/tutorialText4.json",npc4Pos,npc1Tex));
    interactables.emplace_back(std::make_unique<DialogueObject>("assets/Dialogues/tutorialText5.json",npc5Pos,npc1Tex));

    tempVec = {86*32,36*32};
    interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec,SceneEnums::IceBoss, sceneName));

    tempVec =  {39 * 32, 97 * 32 };
    interactables.emplace_back(std::make_unique<Coal>(tempVec));


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
}

void Tutorial::Update() {
    Scene::Update();

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
        if(IsKeyDown(KEY_ENTER) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)) {
            heavyAttackTicker++;
        }
        if(IsKeyReleased(KEY_ENTER) || IsGamepadButtonReleased(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)){ //TODO Rework as soon as charge attack works again
            if(heavyAttackTicker >= 100){
                door2Active = false;
                tutorial2 = false;
                tilemap->RemoveCollisionTile();
                tilemap->RemoveCollisionTile();
            }else heavyAttackTicker = 0;
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
}

void Tutorial::Draw() {
    if(door1Active){
        DrawRectangle(door1[0].x,door1[0].y-32,32,64,RED);
    }if(door2Active){
        DrawRectangle(door2[0].x,door2[0].y-32,32,64,RED);
    }
    if(door3Active){
        DrawRectangle(door3[0].x,door3[0].y-32,32,64,RED);
    }

}