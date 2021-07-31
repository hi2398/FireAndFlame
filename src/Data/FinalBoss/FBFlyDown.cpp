//
// Created by Ashty on 26.07.2021.
//

#include "FBFlyDown.h"
#include "FBSpawnE.h"

FBFlyDown::FBFlyDown() {

}

std::shared_ptr<State> FBFlyDown::Update(Actor &actor) {
    --waitCounter;
    actor.SetPosition({94*32,76*32});
    if(waitCounter <= 0){
        return std::make_shared<FBSpawnE>();
    }
    return shared_from_this();;
}

void FBFlyDown::Draw(Actor &actor) {

}
