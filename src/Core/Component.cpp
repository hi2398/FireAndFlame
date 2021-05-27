//
// Created by Adrian on 27/05/2021.
//

#include "Component.h"
#include <utility>

Component::Component(std::weak_ptr<Object> owner) : owner(std::move(owner)){

}
