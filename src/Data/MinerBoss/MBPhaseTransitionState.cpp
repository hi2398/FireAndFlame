#include <iostream>
#include "MBPhaseTransitionState.h"
#include "MinerBoss.h"
#include "MBDecisionState.h"
#include "raymath.h"

MBPhaseTransitionState::MBPhaseTransitionState(Enemy &enemy) : EState(enemy) {
    enemy.SetInvulnerable(true);
    //bullshit bug fix pointer cast
    auto minerBossPt=dynamic_cast<MinerBoss*>(&enemy);
    minerBossPt->EnableDebris();
    textureRec={32, 64 ,32, 32};

}

std::shared_ptr<EState> MBPhaseTransitionState::Update(Enemy &enemy) {
    auto minerBoss=dynamic_cast<MinerBoss&>(enemy);
    switch (currentStep) {

        case TransitionStep::MoveToStart:
            MoveToStart(enemy);
            break;
        case TransitionStep::Jump:
            Jump(enemy);
            break;
        case TransitionStep::MoveToEnd:
            MoveToEnd(enemy);
            break;
    }


    if (done) {
        //bullshit bug fix pointer cast
        enemy.SetInvulnerable(false);
        auto minerBossPt=dynamic_cast<MinerBoss*>(&enemy);
        minerBossPt->SetMinerBossPhase(MinerBossPhase::Second);
        return std::make_shared<MBDecisionState>(enemy);
    } else return shared_from_this();
}

void MBPhaseTransitionState::MoveToStart(Enemy &enemy) {
    --animTimer;
    textureRec={0, 32, 32, 32};
    if (animTimer<=30){
        textureRec={32, 32, 32, 32};
    }
    if (animTimer<=15){
        textureRec={64, 32, 32, 32};
    }
    if (animTimer<=0){
        textureRec={0, 32, 32, 32};
        animTimer=45;

    }
    enemy.SetDirection(RIGHT);
    float newX = enemy.GetPosition().x + enemy.GetEnemyMovementSpeed();

     if (Vector2Distance({newX, enemy.GetPosition().y}, jumpStart) <= 3.f){
        currentStep=TransitionStep::Jump;
        enemy.SetPosition(jumpStart);

        jumpStartLoc=enemy.GetPosition();
    } else enemy.SetPosition({newX, enemy.GetPosition().y});


}

void MBPhaseTransitionState::Draw(Enemy &actor) {
    auto* minerBoss =dynamic_cast<MinerBoss*>(&actor);
    minerBoss->DrawDirectional(minerBoss->GetPosition(), minerBoss->GetTexture(), textureRec);
}

void MBPhaseTransitionState::Jump(Enemy &enemy) {


    if (Vector2Distance(enemy.GetPosition(), nextJumpLoc) <=3.f){
        enemy.SetPosition(nextJumpLoc);
        lerpAlpha=0.f;
        --jumpsLeft;
        textureRec={64, 64 ,32, 32};
        if (jumpsLeft==0) {
            currentStep=TransitionStep::MoveToEnd;
            targetFloorLocStart=enemy.GetPosition();
        }
        jumpStartLoc=enemy.GetPosition();
        if (enemy.GetDirection()==LEFT){
            enemy.SetDirection(RIGHT);
            nextJumpLoc.x=jumpStartLoc.x+64;
            nextJumpLoc.y=jumpStartLoc.y-64;
        } else {
            enemy.SetDirection(LEFT);
            nextJumpLoc.x=jumpStartLoc.x-64;
            nextJumpLoc.y=jumpStartLoc.y-64;
        }
    } else {
        enemy.SetPosition(Vector2Lerp(jumpStartLoc, nextJumpLoc, lerpAlpha));
        lerpAlpha+=0.03f;
        textureRec={32, 64 ,32, 32};
    }

}

void MBPhaseTransitionState::MoveToEnd(Enemy &enemy) {
    if (!correctZ){
        textureRec={64, 64 ,32, 32};
        enemy.SetDirection(LEFT);
        if (Vector2Distance(enemy.GetPosition(), targetFloorLoc)<=3.f){
            enemy.SetPosition(targetFloorLoc);
            correctZ=true;
            lerpAlpha=0.f;
        } else {
            enemy.SetPosition(Vector2Lerp(targetFloorLocStart, targetFloorLoc, lerpAlpha));
            lerpAlpha+=0.05f;
        }
        return;
    }

    switch (endJumpStep) {
        case 0:
            //move two tiles left
            --animTimer;
            textureRec={0, 32, 32, 32};
            if (animTimer<=30){
                textureRec={32, 32, 32, 32};
            }
            if (animTimer<=15){
                textureRec={64, 32, 32, 32};
            }
            if (animTimer<=0){
                textureRec={0, 32, 32, 32};
                animTimer=45;

            }
            if (Vector2Distance(enemy.GetPosition(), moveTwoLeftEnd) <=3.f){
                enemy.SetPosition(moveTwoLeftEnd);
                lerpAlpha=0.f;
                ++endJumpStep;
            } else {
                enemy.SetPosition(Vector2Lerp(targetFloorLoc, moveTwoLeftEnd, lerpAlpha));
                lerpAlpha+=0.03f;
            }
            break;
        case 1:
            //little jump up
            textureRec={32, 64, 32, 32};
            if (Vector2Distance(enemy.GetPosition(), jumpHighestPoint) <=3.f){
                enemy.SetPosition(jumpHighestPoint);
                lerpAlpha=0.f;
                ++endJumpStep;
            } else {
                enemy.SetPosition(Vector2Lerp(moveTwoLeftEnd, jumpHighestPoint, lerpAlpha));
                lerpAlpha+=0.06f;
            }
            break;
        case 2:
            //fall down
            textureRec={64, 64, 32, 32};
            if (Vector2Distance(enemy.GetPosition(), jumpDown) <=3.f){
                enemy.SetPosition(jumpDown);
                lerpAlpha=0.f;
                ++endJumpStep;
                done=true;
            } else {
                enemy.SetPosition(Vector2Lerp(jumpHighestPoint, jumpDown, lerpAlpha));
                lerpAlpha+=0.03f;
            }
            break;

    }
}


