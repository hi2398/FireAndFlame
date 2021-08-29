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


NeutralArea::NeutralArea(){
    playerCharacter->SetPosition(playerStart);
    playerCharacter->active = true;
    playerCharacter->SetHealth(100);
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Tilemap_1.json","assets/Tilemaps/Neutral_Area_Tilemap.json");
    interactables.emplace_back(std::make_unique<Coal>(playerCharacter->GetPosition()));


    Vector2 tempVec= {106*32,86*32};
    interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec,SceneEnums::AreaOne));
    tempVec= {15*32,77*32};
    interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec,SceneEnums::AreaTwo));
    tempVec= {69*32,65*32};
    interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec,SceneEnums::AreaThree));
    Vector2 vec2{playerStart.x + 32, playerStart.y};
    Vector2 vec3{playerStart.x + 10 * 32, playerStart.y};
    interactables.emplace_back(std::make_unique<Coal>(vec3));
  
    Vector2 vec4{ 54 * 32, 91 * 32 };
    /* TODO Add Statue and Schilder after receiving dialogue files
    Statue 67,92
    Schild 58, 92
    Schild 72,92
    Schild 57,88
     */
    
    switch (6)
    {
    case 0:
        enemies.emplace_back(std::make_unique<Miner>(vec2, EnemyLevel::Low));
        enemies.emplace_back(std::make_unique<Miner>(vec2, EnemyLevel::Medium));
        enemies.emplace_back(std::make_unique<Miner>(vec2, EnemyLevel::High));
        break;
    case 1:
        enemies.emplace_back(std::make_unique<SpiderBot>(vec2, EnemyLevel::Low));
        /*enemies.emplace_back(std::make_unique<SpiderBot>(vec2, EnemyLevel::Medium));*/
        break;
    case 2:
        enemies.emplace_back(std::make_unique<Howler>(vec2, EnemyLevel::Low));
        enemies.emplace_back(std::make_unique<Howler>(vec2, EnemyLevel::Medium));
        break;
    case 3:
        enemies.emplace_back(std::make_unique<ToastCat>(vec2));
        break;
    case 4:
        for (int i = 0; i < 3; i++) {
			enemies.emplace_back(std::make_unique<Fly>(vec2, EnemyLevel::Low));
			enemies.emplace_back(std::make_unique<Fly>(vec2, EnemyLevel::Medium));
			enemies.emplace_back(std::make_unique<Fly>(vec2, EnemyLevel::High));
        }
        break;
    case 5:
        for (int i = 0; i < 30; i++) {
            enemies.emplace_back(std::make_unique<SpringHog>(vec2, EnemyLevel::Low));
            enemies.emplace_back(std::make_unique<SpringHog>(vec2, EnemyLevel::Medium));
        }
        break;
    case 6:
        enemies.emplace_back(std::make_unique<Saugi>(vec2));
        break;
    default:
        break;
    }

    textureForegroundException = LoadTexture("assets/graphics/backgrounds/NeutralArea/Lower_Foreground.png");
    textureForegroundMain = LoadTexture("assets/graphics/backgrounds/NeutralArea/Upper_Foreground.png");
    textureBackgroundMain = LoadTexture("assets/graphics/backgrounds/NeutralArea/background.png");
    textureBackgroundException = LoadTexture("assets/graphics/backgrounds/NeutralArea/background.png");

    foregroundPos = {0,100};
    backgroundPos = { 0,0};

    //fill background loop vector
    backgroundLoopX = 8;
    backgroundLoopY = 20;
    backgroundException = 0;

    foregroundLoopX = 4;
    foregroundLoopY = 10;
    foregroundException = 7;
}


void NeutralArea::Update() {
    Scene::Update();
}

void NeutralArea::Draw() {
    Scene::Draw();


	if constexpr (DEBUG_BUILD) {
		for (const auto x : tilemap->GetTileColliders()) {
			DrawRectangleLines(x.x, x.y, 32, 32, RED);
		}

	}

    if constexpr (DEBUG_BUILD) {
        if (playerCharacter->GetCanDoubleJump()) {
			DrawText(TextFormat("DoubleJump ENABLED", playerCharacter->GetCanDash()), playerCharacter->GetPosition().x, playerCharacter->GetPosition().y - 100, 10, WHITE);
        }
        else {
            DrawText(TextFormat("DoubleJump DISABLED", playerCharacter->GetCanDash()), playerCharacter->GetPosition().x, playerCharacter->GetPosition().y - 100, 10, WHITE);
        }
        
    }
	
}
