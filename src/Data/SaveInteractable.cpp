#include "SaveInteractable.h"
#include "../Global.h"

void SaveInteractable::Update() {
    if(saveCooldown>0){
        --saveCooldown;
    }

}

void SaveInteractable::Draw() {
    if (saveCooldown!=0){
        DrawTextureV(lampOn, position, WHITE);
    } else {
        DrawTextureV(lampOff, position, WHITE);
    }

}

void SaveInteractable::Interact(Actor &actor) {

    PlayerCharacter* player=dynamic_cast<PlayerCharacter*>(&actor);
    if (player){
        if (saveCooldown==0){ //only save every 2 mins at most
            if (DEBUG_BUILD){
                std::cout << "Saving" << std::endl;
            }
            sceneManager->SaveGame("./Saves/", sceneManager->GetSaveSlot());
            hud->ShowSaveNotification();
            playerCharacter->SetHealth(playerCharacter->GetHealth()+50);
            saveCooldown=cooldown;
        }
    }
}

SaveInteractable::~SaveInteractable()
{
    UnloadTexture(lampOff);
    UnloadTexture(lampOn);
}

SaveInteractable::SaveInteractable(Vector2 pos) : Interactable(InteractableType::Save){
    position=pos;
    interactionZone={position.x-32, position.y-32, 96, 96};
    lampOn= LoadTexture("assets/graphics/OtherObjects/Oil_Lamp_On.png");
    lampOff= LoadTexture("assets/graphics/OtherObjects/Oil_Lamp_Off.png");
}
