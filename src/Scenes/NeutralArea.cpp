#include "NeutralArea.h"
#include "raylib.h"
#include "../Global.h"
#include "../Core/Interactable.cpp"
#include "../Core/Coal.cpp"

void NeutralArea::Update() {

    if (CheckCollisionRecs(ground, playerCharacter->playerHitbox)) {
        playerCharacter->isGrounded = true;
    }
    else {
        playerCharacter->isGrounded = false;
    }
    if (coals->GetEnabled() == true)
    {
        if (CheckCollisionRecs(ground, coals->GetHitbox()))
        {
            coals->SetGrounded(true);
        }
        else
        {
            coals->SetGrounded(false);
        }
        if (CheckCollisionRecs(playerCharacter->playerHitbox, coals->GetHitbox()))
        {
            coals->Interact();
        }
        coals->Update();
    }
    else
    {
        if (Coaltimer == 0) {
            Vector2 pStartVectorCoal;
            pStartVectorCoal.x = 100;
            pStartVectorCoal.y = -50;
            coals->SetPosition(pStartVectorCoal);
            coals->SetEnabled(true);
            Coaltimer = 60;
        }
        else
        {
            Coaltimer--;
        }
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
    coals->Draw();
    /*for (const auto& i : coals) {
        i->Draw();
    }*/
}

NeutralArea::NeutralArea() {
    
}
