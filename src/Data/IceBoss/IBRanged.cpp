#include <iostream>
#include "IBRanged.h"
#include "IBSeek.h"
#include "IceBoss.h"

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
    auto& iceBoss=dynamic_cast<IceBoss&>(actor);
    DrawTextureRec(iceBoss.GetMovingTexture(),
                   { 0,
                     0,
                     (float) iceBoss.GetMovingTexture().width * actor.GetDirection(),
                     (float) iceBoss.GetMovingTexture().height },
                   actor.GetPosition(),
                   WHITE);
}
