#include "NeutralArea.h"
#include "raylib.h"
#include "../Global.h"

void NeutralArea::Update() {
    //decrease player health every second
    generalTimer++;
    if (generalTimer >= 30) {
        generalTimer = 0;
        playerCharacter->SetHealth(playerCharacter->GetHealth() - 1);
    }

    //player X ground collision
    if (CheckCollisionRecs(ground, playerCharacter->playerHitbox)) {
        playerCharacter->isGrounded = true;
    }
    else {
        playerCharacter->isGrounded = false;
    }

    //coal X player && coal X ground collision
    if (coals->GetEnabled())
    {
		coals->Update();
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
        
    }
    else
    {
        if (coalTimer == 0) {
            Vector2 pStartVectorCoal;
            pStartVectorCoal.x = 100;
            pStartVectorCoal.y = -50;
            coals->SetPosition(pStartVectorCoal);
            coals->SetEnabled(true);
            coalTimer = 60;
        }
        else
        {
            coalTimer--;
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
