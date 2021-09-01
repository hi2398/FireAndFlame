#include "Deathzone.h"

Deathzone::Deathzone(Vector2 location) : Interactable(InteractableType::Other){
    interactionZone = {location.x,location.y,3200,200};
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

}

Deathzone::~Deathzone() {

}