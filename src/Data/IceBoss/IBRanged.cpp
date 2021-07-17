#include <iostream>
#include "IBRanged.h"
#include "IBSeek.h"

IBRanged::IBRanged() {

}

std::shared_ptr<State> IBRanged::Update(Actor &actor) {

    std::cout << "IBRanged\n";

    //if ranged attack is done return to seek
    return std::make_shared<IBSeek>();
    //execute ranged attack timestep then return self
    return shared_from_this();
}

void IBRanged::Draw(Actor &actor) {

}
