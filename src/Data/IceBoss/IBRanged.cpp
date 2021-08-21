#include <iostream>
#include "IBRanged.h"
#include "IBSeek.h"
#include "IceBoss.h"
#include "raymath.h"
#include "../../Global.h"
#include "IceZone.h"

IBRanged::IBRanged(Vector2 startLocation, Enemy &enemy) : EState(enemy) {
    this->startLocation=startLocation;
    barrel= LoadTexture("assets/Bosses/IceBoss/Barrel.png");
    barrelPos=startLocation;
    targetLocation=playerCharacter->GetPosition();
    texRec={0, 0, 32, 32};
}

std::shared_ptr<EState> IBRanged::Update(Enemy &enemy) {
    auto* iceBoss=dynamic_cast<IceBoss*>(&enemy);

    switch (rangedStep) {
        case RangedStep::WindUp:
            WindUp(iceBoss);
            break;
        case RangedStep::Throw:
            ThrowBarrel(iceBoss);
            break;
        case RangedStep::JumpDown:
            JumpDown(iceBoss);
            break;
    }



    if (jumpTimer==0) return std::make_shared<IBSeek>(enemy);
    return shared_from_this();
}

void IBRanged::Draw(Enemy &enemy) {
    auto* iceBoss=dynamic_cast<IceBoss*>(&enemy);
    iceBoss->DrawDirectional(iceBoss->GetPosition(), iceBoss->GetTexture(), texRec);
    if(0 < animTimer && animTimer < 90)DrawTextureV(barrel, barrelPos, WHITE);
}

void IBRanged::ThrowBarrel(IceBoss* iceBoss) {
    texRec={static_cast<float>(96*iceBoss->GetPhase()), static_cast<float>(96*iceBoss->GetPhase()), 32, 32};
    barrelPos= Vector2Lerp(startLocation, targetLocation, 1.f-animTimer/90.f);
    //TODO: play animation
    --animTimer;

    if (animTimer==0) {
        Vector2 spawnLoc{targetLocation.x-32, targetLocation.y+32};
        sceneManager->AddInteractable(std::make_unique<IceZone>(spawnLoc));
        rangedStep=RangedStep::JumpDown;
    }
}

void IBRanged::JumpDown(IceBoss *iceBoss) {
    texRec={static_cast<float>(96*iceBoss->GetPhase()+32), static_cast<float>(96*iceBoss->GetPhase()+32), 32, 32};

    iceBoss->SetPosition(Vector2Lerp(startLocation, jumpEnd, 1.f-jumpTimer/60.f));
    --jumpTimer;

}

void IBRanged::WindUp(IceBoss *iceBoss) {

    --windUpTimer;

    if (windUpTimer<=30){
        texRec={static_cast<float>(96*iceBoss->GetPhase())+64, static_cast<float>(96*iceBoss->GetPhase())+96, 32, 32};
    } else {
        texRec={static_cast<float>(96*iceBoss->GetPhase())+64, static_cast<float>(96*iceBoss->GetPhase())+64, 32, 32};
    }

    if (windUpTimer==0) {
        rangedStep=RangedStep::Throw;
    }
}
