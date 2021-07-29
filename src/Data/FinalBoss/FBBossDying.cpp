//
// Created by Ashty on 29.07.2021.
//

#include "FBBossDying.h"
#include "../../Global.h"

FBBossDying::FBBossDying() {
    sceneManager->RemoveAllInteractables();
    playerCharacter->SetHealth(100);
}

std::shared_ptr<State> FBBossDying::Update(Actor &actor) {
    return shared_from_this();
}

void FBBossDying::Draw(Actor &actor) {

}