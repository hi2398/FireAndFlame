#include "IceZone.h"
#include "../../Global.h"

IceZone::IceZone(Vector2 location) : Interactable(InteractableType::IceZone) {
   position=location;
   iceZone = LoadTexture("assets/Bosses/IceBoss/Ice_Zone.png");
   interactionZone={position.x + 10, position.y - 1, 76, 20};
}

void IceZone::Update() {
    --lifetime;
    if (lifetime==0) playerCharacter->SetCanMove(true), markedDestroy = true;
}

void IceZone::Draw() {
    DrawTextureV(iceZone, position, WHITE);
    if (freezeActivated) freezeEffect->Draw();
}

void IceZone::Interact(Actor &actor) {
    if (actor.GetType()==ObjectTypes::Player){
        if (damageTimer == 0) {
            if (!freezeActivated) freezeEffect = std::make_unique<FreezeVisual>(playerCharacter->GetPosition(), 60);
            playerCharacter->SetCanMove(false);
            freezeActivated = true;
        }
        if (damageTimer!=0){
            --damageTimer;
        } else {
            playerCharacter->SetHealth(playerCharacter->GetHealth()-1);
            damageTimer=damageInterval;

        }
    }
}
