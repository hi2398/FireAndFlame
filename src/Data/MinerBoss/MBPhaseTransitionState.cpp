#include <iostream>
#include "MBPhaseTransitionState.h"
#include "MinerBoss.h"
#include "MBDecisionState.h"
#include "raymath.h"

MBPhaseTransitionState::MBPhaseTransitionState(Enemy &enemy) : EState(enemy) {

}

std::shared_ptr<EState> MBPhaseTransitionState::Update(Enemy &actor) {
    auto minerBoss=dynamic_cast<MinerBoss&>(actor);
    switch (currentStep) {

        case TransitionStep::MoveToStart:
            MoveToStart(actor);
            break;
        case TransitionStep::Jump:
            Jump(actor);
            break;
        case TransitionStep::MoveToEnd:
            MoveToEnd(actor);
            break;
    }

    if (done) {
        minerBoss.SetMinerBossPhase(MinerBossPhase::Second);
        return std::make_shared<MBDecisionState>(actor);
    } else return shared_from_this();
}

void MBPhaseTransitionState::MoveToStart(Enemy &enemy) {
    enemy.SetDirection(RIGHT);
    float newX = enemy.GetPosition().x + enemy.GetEnemyMovementSpeed();

     if (Vector2Distance({newX, enemy.GetPosition().y}, jumpStart) <= 3.f){
        currentStep=TransitionStep::Jump;
        enemy.SetPosition(jumpStart);
        jumpStartLoc=enemy.GetPosition();
    } else enemy.SetPosition({newX, enemy.GetPosition().y});

}

void MBPhaseTransitionState::Draw(Enemy &actor) {
    auto minerBoss=dynamic_cast<MinerBoss&>(actor);
    minerBoss.DrawDirectional(minerBoss.GetPosition(), minerBoss.GetTexture());
}

void MBPhaseTransitionState::Jump(Enemy &enemy) {

    if (Vector2Distance(enemy.GetPosition(), nextJumpLoc) <=3.f){
        enemy.SetPosition(nextJumpLoc);
        lerpAlpha=0.f;
        --jumpsLeft;
        if (jumpsLeft==0) {
            currentStep=TransitionStep::MoveToEnd;
            targetFloorLocStart=enemy.GetPosition();
        }
        jumpStartLoc=enemy.GetPosition();
        if (enemy.GetDirection()==LEFT){
            enemy.SetDirection(RIGHT);
            nextJumpLoc.x=jumpStartLoc.x-64;
            nextJumpLoc.y=jumpStartLoc.y-64;
        } else {
            enemy.SetDirection(LEFT);
            nextJumpLoc.x=jumpStartLoc.x+64;
            nextJumpLoc.y=jumpStartLoc.y-64;
        }
    } else {
        enemy.SetPosition(Vector2Lerp(jumpStartLoc, nextJumpLoc, lerpAlpha));
        lerpAlpha+=0.03f;
    }

}

void MBPhaseTransitionState::MoveToEnd(Enemy &enemy) {
    if (!correctZ){
        if (Vector2Distance(enemy.GetPosition(), targetFloorLoc)<=3.f){
            enemy.SetPosition(targetFloorLoc);
            correctZ=true;
        } else {
            enemy.SetPosition(Vector2Lerp(targetFloorLocStart, targetFloorLoc, lerpAlpha));
            lerpAlpha+=0.03f;
        }
        return;
    }

    switch (endJumpStep) {
        case 0:
            //move two tiles left
            break;
        case 1:
            //little jump up
            break;
        case 2:
            //fall down
            break;

    }
}
