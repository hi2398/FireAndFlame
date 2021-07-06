//
// Created by Adrian on 27/05/2021.
//

#include "Interactable.h"
#include "Object.h"

Interactable::Interactable(InteractableType interactableType) : Object(ObjectTypes::Interactable) {
    this->interactableType=interactableType;
}

InteractableType Interactable::GetInteractableType() const {
    return interactableType;
}

Rectangle Interactable::GetInteractionZone() const {
    return interactionZone;
}

