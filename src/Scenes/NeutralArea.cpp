#include "NeutralArea.h"
#include "raylib.h"
#include "../Global.h"

void NeutralArea::Update() {

    if (CheckCollisionRecs(ground, playerCharacter->playerHitbox)) {
        playerCharacter->isGrounded = true;
    }
    else {
        playerCharacter->isGrounded = false;
    }

    for (const auto& x: enemies) {
    x->Update();
    }
}

void NeutralArea::Draw() {
    ClearBackground(LIGHTGRAY);
    for (int i = 0; i < 7;  i++) {
        DrawRectangle(-1000 + i * 300, 40, 100, 300, GRAY);
        DrawRectangle(-900 + i * 300, 40, 100, 300, BROWN);
        DrawRectangle(-800 + i * 300, 40, 100, 300, MAROON);
    }
    for (const auto& x: enemies) {
        x->Draw();
    }
}

NeutralArea::NeutralArea() {
    
}
