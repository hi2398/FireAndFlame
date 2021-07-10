#include "NeutralArea.h"
#include "raylib.h"
#include "../Data/Miner.h"
#include "../Core/SaveGameState.h"


NeutralArea::NeutralArea(){
    playerCharacter->SetPosition({ 50 * 32, 36 * 32 });
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
    interactables.emplace_back(std::make_unique<DialogObject>("assets/Dialogues/testText.json",tempVec,tempTex));
    Vector2 vec2{50*32-100, 36*32};
    enemies.emplace_back(std::make_unique<Miner>(vec2));
}


void NeutralArea::Update() {
    if constexpr (DEBUG_BUILD) {
        if (IsKeyPressed(KEY_PERIOD)) {
            SaveGameState saveGameState;
            saveGameState.SaveGame("./savefileDEBUG.json");
        }
    }
}

void NeutralArea::Draw() {




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
