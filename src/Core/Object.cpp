//
// Created by Adrian on 27/05/2021.
//

#include "Object.h"

ObjectTypes Object::GetType() const {
    return type;
}

Object::Object(ObjectTypes type) : type(type) {

}
