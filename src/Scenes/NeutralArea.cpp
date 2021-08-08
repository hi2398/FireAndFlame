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

    Vector2 tempVec= {132*32,83*32};
    interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec,SceneEnums::AreaOne));
    Vector2 vec2{20*32, 36*32};
    Vector2 vec3{10 * 32, 36*32};
    Vector2 vec4{ 54 * 32, 91 * 32 };
    /* TODO Add Statue and Schilder after receiving dialogue files
     Statue 67,92
    Schild 58, 92
    Schild 72,92
    Schild 57,88
     */
    
    switch (4)
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
        enemies.emplace_back(std::make_unique<SpringHog>(vec2, EnemyLevel::Low));
        enemies.emplace_back(std::make_unique<SpringHog>(vec2, EnemyLevel::Medium));
        break;
    case 6:
        enemies.emplace_back(std::make_unique<Saugi>(vec2));
        break;
    default:
        break;
    }

    textureForeground = LoadTexture("assets/graphics/backgrounds/background1.png");
    textureMiddleground = LoadTexture("assets/graphics/backgrounds/background2.png");
    textureBackground = LoadTexture("assets/graphics/backgrounds/background3.png");

    foregroundPosition = {playerStart};
    middlegroundPosition = {playerStart};
    backgroundPosition = { playerStart};
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
