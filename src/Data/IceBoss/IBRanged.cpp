#include <iostream>
#include "IBRanged.h"
#include "IBSeek.h"
#include "IceBoss.h"
#include "raymath.h"
#include "../../Global.h"
#include "IceZone.h"

IBRanged::IBRanged(Vector2 startLocation) {
    this->startLocation=startLocation;
    barrel= LoadTexture("assets/Bosses/IceBoss/Barrel.png");
    barrelPos=startLocation;
}

std::shared_ptr<State> IBRanged::Update(Actor &actor) {

    std::cout << "IBRanged\n";
    if (animTimer==0) {
        Vector2 spawnLoc{targetLocation.x-32, targetLocation.y+32};
        sceneManager->AddInteractable(std::make_unique<IceZone>(spawnLoc));
        return std::make_shared<IBSeek>();
    }
    //if ranged attack is done return to seek
    barrelPos= Vector2Lerp(startLocation, targetLocation, 1.f-animTimer/90.f);
    //TODO: play animation
    --animTimer;
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
    DrawTextureV(barrel, barrelPos, WHITE);
}
