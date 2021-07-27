//
// Created by Ashty on 26.07.2021.
//

#include "FBSwordAtk.h"

FBSwordAtk::FBSwordAtk() {

}

std::shared_ptr<State> FBSwordAtk::Update(Actor &actor) {
    return shared_from_this();;
}

void FBSwordAtk::Draw(Actor &actor) {

}
