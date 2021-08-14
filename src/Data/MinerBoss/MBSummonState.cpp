#include "MBSummonState.h"
#include "MinerBoss.h"
#include "../../Global.h"
#include "MBDecisionState.h"
#include "raymath.h"
#include "../Enemies/SpringHog.h"

MBSummonState::MBSummonState(Enemy &enemy) : EState(enemy) {
    if constexpr(DEBUG_ENEMY_STATES){
        std::cout << "Miner Boss State Transition to: Summon\n";
    }

    //determine direction to attack
    if ((jumpStart.x-enemy.GetPosition().x) >=0){
        enemy.SetDirection(RIGHT);
    } else  {
        enemy.SetDirection(LEFT);
    }
}

std::shared_ptr<EState> MBSummonState::Update(Enemy &enemy) {

    switch (summonStep) {

        case SummonSteps::MoveToSpot:
            MoveToSpot(enemy);
            break;
        case SummonSteps::JumpUp:
            JumpUp(enemy);
            break;
        case SummonSteps::Summon:
            Summon(enemy);
            break;
        case SummonSteps::ReturnToGround:
            ReturnToGround(enemy);
            break;
        case SummonSteps::Done:
            return std::make_shared<MBDecisionState>(enemy);
            break;
    }
    return shared_from_this();
}

void MBSummonState::Draw(Enemy &actor) {
    auto minerBoss=dynamic_cast<MinerBoss&>(actor);
    minerBoss.DrawDirectional(minerBoss.GetPosition(), minerBoss.GetTexture());
}

void MBSummonState::MoveToSpot(Enemy &enemy) {
    float newX = enemy.GetPosition().x + enemy.GetEnemyMovementSpeed()*enemy.GetDirection();

    if (Vector2Distance({newX, enemy.GetPosition().y}, jumpStart) <= 3.f){
        summonStep=SummonSteps::JumpUp;
        enemy.SetPosition(jumpStart);
    } else enemy.SetPosition({newX, enemy.GetPosition().y});

}

void MBSummonState::JumpUp(Enemy &enemy) {

    switch (jumpSubstep) {
        case 0:
            if (Vector2Distance(enemy.GetPosition(), highSpot)<=3.f){
                enemy.SetPosition(highSpot);
                lerpAlpha=0.f;
                ++jumpSubstep;
            } else {
                enemy.SetPosition(Vector2Lerp(jumpStart, highSpot, lerpAlpha));
                lerpAlpha+=0.05f;
            }
            break;
        case 1:
            if (Vector2Distance(enemy.GetPosition(), summonSpot)<=3.f){
                enemy.SetPosition(summonSpot);
                lerpAlpha=0.f;
                summonStep=SummonSteps::Summon;
            } else {
                enemy.SetPosition(Vector2Lerp(highSpot, summonSpot, lerpAlpha));
                lerpAlpha+=0.2f;
            }
            break;
    }

}

void MBSummonState::Summon(Enemy &enemy) {
    --summonTimer;
    if (summonTimer==1) {
        sceneManager->AddEnemy(std::make_unique<SpringHog>(spawn, EnemyLevel::Medium));
        sceneManager->AddEnemy(std::make_unique<SpringHog>(spawn2, EnemyLevel::Medium));
    }

    if (summonTimer<=0 && sceneManager->GetEnemies().size()==1) summonStep=SummonSteps::ReturnToGround;
}

void MBSummonState::ReturnToGround(Enemy &enemy) {
    enemy.SetDirection(LEFT);
    switch (returnSubstep) {
        case 0:
            if (Vector2Distance(enemy.GetPosition(), highSpot)<=3.f){
                enemy.SetPosition(highSpot);
                lerpAlpha=0.f;
                ++returnSubstep;
            } else {
                enemy.SetPosition(Vector2Lerp(summonSpot, highSpot, lerpAlpha));
                lerpAlpha+=0.2f;
            }
            break;
        case 1:
            if (Vector2Distance(enemy.GetPosition(), jumpStart)<=3.f){
                enemy.SetPosition(jumpStart);
                lerpAlpha=0.f;
                summonStep=SummonSteps::Done;
            } else {
                enemy.SetPosition(Vector2Lerp(highSpot, jumpStart, lerpAlpha));
                lerpAlpha+=0.05f;
            }

            break;
    }

}
