#include "NeutralArea.h"
#include "raylib.h"
#include "../Global.h"


NeutralArea::NeutralArea() {
    tilemap=std::make_unique<Tilemap>("assets/Tilemaps/Testmap/Placehalter_2.json","assets/Tilemaps/Testmap/Map_2.json");
}

void NeutralArea::Update() {
    //decrease player health every second
    generalTimer++;
    if (generalTimer >= 30) {
        generalTimer = 0;
        playerCharacter->SetHealth(playerCharacter->GetHealth() - 1);
    }

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

 
    for (const auto& x: enemies) {
        x->Draw();
    }
    coals->Draw();

    /*for (const auto& i : coals) {
        i->Draw();
    }*/
    tilemap->Draw();
}
