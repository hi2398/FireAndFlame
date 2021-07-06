//
// Created by Adrian on 27/05/2021.
//

#include "Interactable.h"
#include "Object.h"

ObjectTypes Object::GetType() const {
    return type;
}

Object::Object(ObjectTypes type) : type(type) {

}

Vector2 Object::GetPosition() const {
    return position;
}

void Object::SetPosition(Vector2 position) {
    this->position=position;
}

bool Object::IsMarkedDestroy() const {
    return markedDestroy;
}