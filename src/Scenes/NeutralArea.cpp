#include "NeutralArea.h"
#include "raylib.h"
#include "../Global.h"


NeutralArea::NeutralArea() {
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Placehalter_2.json","assets/Tilemaps/Testmap/Map_2.json");
}

void NeutralArea::Update() {
    Rectangle tempVec = {0,0,32,32};
    for(const auto& x: tilemap->GetWorldPos()){
        tempVec.x = x.x;
        tempVec.y = x.y;
        if(CheckCollisionRecs(tempVec, playerCharacter->playerHitbox)) {
            playerCharacter->isGrounded = true;
            break;
        }else {
            playerCharacter->isGrounded = false;
        }
    }

    for (const auto& x: enemies) {
    x->Update();
    }
}

void NeutralArea::Draw() {
    ClearBackground(LIGHTGRAY);
    for (const auto& x: enemies) {
        x->Draw();
    }
    tilemap->Draw();
}
