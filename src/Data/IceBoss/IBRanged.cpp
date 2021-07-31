#include <iostream>
#include "IBRanged.h"
#include "IBSeek.h"
#include "IceBoss.h"
#include "raymath.h"
#include "../../Global.h"
#include "IceZone.h"

IBRanged::IBRanged(Vector2 startLocation){
    this->startLocation=startLocation;
    barrel= LoadTexture("assets/Bosses/IceBoss/Barrel.png");
    barrelPos=startLocation;
}

std::shared_ptr<State> IBRanged::Update(Actor &actor) {
    if (jumpTimer==0) return std::make_shared<IBSeek>();
    if (jumpStarted) { //jump

        actor.SetPosition(Vector2Lerp(startLocation, jumpEnd, 1.f-jumpTimer/60.f));
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

void IBRanged::Draw(Actor &actor) {
    auto& iceBoss=dynamic_cast<IceBoss&>(actor);
    iceBoss.DrawDirectional(iceBoss.GetPosition(), iceBoss.GetMovingTexture());
    if(0 < animTimer && animTimer < 90)DrawTextureV(barrel, barrelPos, WHITE);
}
