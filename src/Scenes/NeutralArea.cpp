#include "NeutralArea.h"
#include "raylib.h"
#include "../Data/Miner.h"


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

}

void NeutralArea::Draw() {




	if constexpr (DEBUG_BUILD) {
		for (const auto x : tilemap->GetTileColliders()) {
			DrawRectangleLines(x.x, x.y, 32, 32, RED);
		}
	}

	DrawText(TextFormat("%i", playerCharacter->GetCanDoubleJump()), playerCharacter->GetPosition().x, playerCharacter->GetPosition().y-100, 30, WHITE);
}
