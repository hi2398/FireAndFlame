//
// Created by Adrian on 27/05/2021.
//

#include "Actor.h"

Actor::Actor(ObjectTypes type) : Object(type) {

}

template<class T>
std::unique_ptr<Component> Actor::AddComponent(T) {
    components.emplace_back(std::make_unique<T>(weak_from_this()));
}
