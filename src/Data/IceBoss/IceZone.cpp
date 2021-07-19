#include "IceZone.h"

IceZone::IceZone(Vector2 location) : Interactable(InteractableType::IceZone) {

}

void IceZone::Update() {
    Interactable::Update();
}

void IceZone::Draw() {
    Interactable::Draw();
}

void IceZone::Interact(Actor &actor) {
    //TODO: When player interacts, drain health
}
