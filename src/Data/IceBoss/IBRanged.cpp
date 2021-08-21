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
    if (jumpTimer==0) return std::make_shared<IBSeek>(enemy);
    if (jumpStarted) { //jump
        texRec={static_cast<float>(32*iceBoss->GetPhase()), static_cast<float>(32*iceBoss->GetPhase()), 32, 32};

        enemy.SetPosition(Vector2Lerp(startLocation, jumpEnd, 1.f-jumpTimer/60.f));
        --jumpTimer;
    }
    if (animTimer==0) {
        Vector2 spawnLoc{targetLocation.x-32, targetLocation.y+32};
        sceneManager->AddInteractable(std::make_unique<IceZone>(spawnLoc));
        jumpStarted=true;
        return shared_from_this();
    }
    //if ranged attack is done return to seek
    barrelPos= Vector2Lerp(startLocation, targetLocation, 1.f-animTimer/90.f);
    //TODO: play animation
    --animTimer;
    return shared_from_this();
}

void IBRanged::Draw(Enemy &enemy) {
    auto* iceBoss=dynamic_cast<IceBoss*>(&enemy);
    iceBoss->DrawDirectional(iceBoss->GetPosition(), iceBoss->GetTexture(), texRec);
    if(0 < animTimer && animTimer < 90)DrawTextureV(barrel, barrelPos, WHITE);
}
