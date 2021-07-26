#include <iostream>
#include "IBMinions.h"
#include "IBSeek.h"
#include "IceBoss.h"

IBMinions::IBMinions() {

}

std::shared_ptr<State> IBMinions::Update(Actor &actor) {

    std::cout << "IBMinions\n";

    //return to seek once phase is done
    return std::make_shared<IBSeek>();
    //return self until all minions defeated
    return shared_from_this();
}

void IBMinions::Draw(Actor &actor) {
    auto& iceBoss=dynamic_cast<IceBoss&>(actor);
    iceBoss.DrawDirectional(iceBoss.GetPosition(), iceBoss.GetMovingTexture());
}
