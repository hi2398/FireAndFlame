#include <iostream>
#include "IBMelee.h"
#include "IBSeek.h"
#include "IceBoss.h"

IBMelee::IBMelee() {

}

std::shared_ptr<State> IBMelee::Update(Actor &actor) {

    std::cout << "IBMelee\n";
    //if melee attack is done, decide go back to seek
    return std::make_shared<IBSeek>();


    //as long as melee attack isnt done, continue returning from this
    return shared_from_this();
}

void IBMelee::Draw(Actor &actor) {
    auto& iceBoss=dynamic_cast<IceBoss&>(actor);
    DrawTextureRec(iceBoss.GetMovingTexture(),
                   { 0,
                     0,
                     (float) iceBoss.GetMovingTexture().width * actor.GetDirection(),
                     (float) iceBoss.GetMovingTexture().height },
                   actor.GetPosition(),
                   WHITE);
}
