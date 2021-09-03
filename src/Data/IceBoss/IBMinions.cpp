#include <iostream>
#include "IBMinions.h"
#include "IBSeek.h"
#include "IceBoss.h"
#include "../../Global.h"
#include "../Enemies/Saugi.h"

IBMinions::IBMinions(Enemy& enemy) : EState(enemy) {

}

std::shared_ptr<EState> IBMinions::Update(Enemy &enemy) {



    //return to seek once phase is done
    return std::make_shared<IBSeek>(enemy);
    //return self until all minions defeated
    return shared_from_this();
}

void IBMinions::Draw(Enemy &enemy) {
    auto* iceBoss=dynamic_cast<IceBoss*>(&enemy);
    iceBoss->DrawDirectional(iceBoss->GetPosition(), iceBoss->GetTexture());
}
