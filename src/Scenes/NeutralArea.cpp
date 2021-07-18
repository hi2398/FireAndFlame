#include "NeutralArea.h"
#include "raylib.h"
#include "../Data/Enemies/Miner.h"
#include "raymath.h"


NeutralArea::NeutralArea(){
    playerCharacter->SetPosition(playerStart);
    playerCharacter->active = true;
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Placehalter_2.json","assets/Tilemaps/Testmap/NEUTRAL_AREA.json");
    interactables.emplace_back(std::make_unique<Coal>(playerCharacter->GetPosition()));
    // Delete this section, only for testing
    Vector2 tempVec= playerCharacter->GetPosition();
    tempVec.x+=256;
    // A
    interactables.emplace_back(std::make_unique<SceneChangerObject>(tempVec,SceneEnums::AreaOne));
    //Delete this section, only for testing
    tempVec.x-=512;
    tempVec.y+=64;
    Texture2D tempTex = LoadTexture("assets/graphics/PLAYER.png");
    // A
    interactables.emplace_back(std::make_unique<DialogueObject>("assets/Dialogues/testText.json",tempVec,tempTex));
    Vector2 vec2{20*32-100, 36*32};
    for (int i = 0; i < 10; i++) {
        enemies.emplace_back(std::make_unique<Miner>(vec2));
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
