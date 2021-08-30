#include "NeutralArea.h"
#include "raylib.h"
#include "../Data/Enemies/Miner.h"
#include "../Data/Enemies/ToastCat.h"
#include "../Data/Enemies/Fly.h"
#include "../Data/Enemies/Howler.h"
#include "../Data/Enemies/SpiderBot.h"
#include "../Data/Enemies/SpringHog.h"
#include "../Data/Enemies/Saugi.h"
#include "raymath.h"


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
   
    /* TODO Add Statue and Schilder after receiving dialogue files
    Statue 67,92
    Schild 58, 92
    Schild 72,92
    Schild 57,88
     */
    

    textureForegroundException = LoadTexture("assets/graphics/backgrounds/NeutralArea/Lower_Foreground.png");
    textureForegroundMain = LoadTexture("assets/graphics/backgrounds/NeutralArea/Upper_Foreground.png");
    textureBackgroundMain = LoadTexture("assets/graphics/backgrounds/NeutralArea/background.png");
    textureBackgroundException = LoadTexture("assets/graphics/backgrounds/NeutralArea/background.png");

    switch (lastScene)
    {
    case SceneEnums::MinerBoss:
        playerCharacter->SetPosition({ 104 * 32, 89 * 32 });
        foregroundPos = { 863.4 , -40.8 };
        backgroundPos = { 1439, -633.6 };
        break;
    case SceneEnums::TraitorBoss:
        playerCharacter->SetPosition({ 20 * 32,80 * 32 });
        foregroundPos = { -750, -98.4 };
        backgroundPos = {-1250, -924.8 };
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
