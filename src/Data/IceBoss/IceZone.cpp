#include "IceZone.h"
#include "../../Global.h"

IceZone::IceZone(Vector2 location) : Interactable(InteractableType::IceZone) {
   position=location;
   iceZone = LoadTexture("assets/Bosses/IceBoss/Ice_Zone.png");
   interactionZone={position.x, position.y, 96, 20};
}

void IceZone::Update() {
    --lifetime;
    if (lifetime==0) markedDestroy = true;
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
