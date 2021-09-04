#include "NeutralArea.h"
#include "raylib.h"
#include "../Core/EnemyList.h"
#include "raymath.h"
#include "../Data/Deathzone.h"
#include "../Data/SaveInteractable.h"


NeutralArea::NeutralArea(SceneEnums lastScene) : Scene(SceneEnums::NeutralArea){
    this->lastScene = lastScene;
    playerCharacter->active = true;
    playerCharacter->SetHealth(100);
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Tilemap_1.json","assets/Tilemaps/Neutral_Area_Tilemap.json");
    interactables.emplace_back(std::make_unique<Coal>(playerCharacter->GetPosition()));



    Vector2 tempVec= {106*32,86*32};
    interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec,SceneEnums::AreaOne, sceneName));
    tempVec= {15*32,77*32};
    interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec,SceneEnums::AreaTwo, sceneName));
    tempVec= {69*32,65*32};
    interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec,SceneEnums::AreaThree, sceneName));

    tempVec = {-200, 130*32};
    interactables.emplace_back(std::make_unique<Deathzone>(tempVec));

    tempVec = {59*32,101*32+6};
    Texture2D statueTex = LoadTexture("assets/graphics/statue.png");
    interactables.emplace_back(std::make_unique<DialogueObject>("assets/Dialogues/Neutrale_Ebene_Statue.json",tempVec,statueTex));

    tempVec = {69*32,102*32+3};
    statueTex = LoadTexture("assets/graphics/Sign.png");
    interactables.emplace_back(std::make_unique<DialogueObject>("assets/Dialogues/Neutrale_Ebene_Level_12.json",tempVec,statueTex));

    

    textureForegroundException = LoadTexture("assets/graphics/backgrounds/NeutralArea/Lower_Foreground.png");
    textureForegroundMain = LoadTexture("assets/graphics/backgrounds/NeutralArea/Upper_Foreground.png");
    textureBackgroundMain = LoadTexture("assets/graphics/backgrounds/NeutralArea/background.png");
    textureBackgroundException = LoadTexture("assets/graphics/backgrounds/NeutralArea/background.png");

    switch (lastScene)
    {
    case SceneEnums::MinerBoss:
        playerCharacter->SetPosition({ 86 * 32, 90 * 32 });
        foregroundPos = { 522 , -34.4 };
        backgroundPos = { 871, -604.8 };
        break;
    case SceneEnums::TraitorBoss:
        playerCharacter->SetPosition({ 37 * 32,73 * 32 });
        foregroundPos = { -422.4, -143.2 };
        backgroundPos = {-704, -1094.4 };
        break;
    default:
        playerCharacter->SetPosition(playerStart);
		foregroundPos = { 0,100 };
		backgroundPos = { 0,0 };
        break;
    }
    //fill background loop vector
		backgroundLoopX = 8;
		backgroundLoopY = 20;
		backgroundException = 0;

		foregroundLoopX = 4;
		foregroundLoopY = 8;
		foregroundException = 7;
}


void NeutralArea::Update() {
    Scene::Update();
}

void NeutralArea::Draw() {
    Scene::Draw();
    if constexpr (DEBUG_BUILD) {
        if (playerCharacter->GetCanDoubleJump()) {
			DrawText(TextFormat("DoubleJump ENABLED", playerCharacter->GetCanDash()), playerCharacter->GetPosition().x, playerCharacter->GetPosition().y - 100, 10, WHITE);
        }
        else {
            DrawText(TextFormat("DoubleJump DISABLED", playerCharacter->GetCanDash()), playerCharacter->GetPosition().x, playerCharacter->GetPosition().y - 100, 10, WHITE);
        }
        
    }
	
}
