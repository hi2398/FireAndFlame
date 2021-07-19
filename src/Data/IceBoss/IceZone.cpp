#include "IceZone.h"
#include "../../Global.h"

IceZone::IceZone(Vector2 location) : Interactable(InteractableType::IceZone) {
   position=location;
   iceZone = LoadTexture("assets/Bosses/IceBoss/Ice_Zone.png");
   interactionZone={position.x, position.y-10, 96, 30};
}

void IceZone::Update() {

}

void IceZone::Draw() {
    DrawTextureV(iceZone, position, WHITE);

}

void IceZone::Interact(Actor &actor) {
    if (actor.GetType()==ObjectTypes::Player){
        if (damageTimer!=0){
            --damageTimer;
        } else {
            playerCharacter->SetHealth(playerCharacter->GetHealth()-1);
            damageTimer=damageInterval;
        }
    }
}
