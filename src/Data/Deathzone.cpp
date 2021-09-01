#include "Deathzone.h"

Deathzone::Deathzone(Vector2 location) : Interactable(InteractableType::Other){
    interactionZone = {location.x,location.y,6400,200};
}

void Deathzone::Interact(Actor &actor) {
    playerCharacter->SetHealth(0);
}

Rectangle Deathzone::GetHitbox() {
    return interactionZone;
}

void Deathzone::Update() {

}

void Deathzone::Draw() {
    //DrawRectangleRec(interactionZone,GREEN);
}

Deathzone::~Deathzone() {

}