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
    textureRec={0, 32, 32, 32};
    currentAnimTimer=animTimer;
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
    minerBoss.DrawDirectional(minerBoss.GetPosition(), minerBoss.GetTexture(), textureRec);
}

void MBSummonState::MoveToSpot(Enemy &enemy) {
    float newX = enemy.GetPosition().x + enemy.GetEnemyMovementSpeed()*enemy.GetDirection();
    --currentAnimTimer;
    if (currentAnimTimer<=20){
        textureRec={64, 32, 32, 32};
    } else if (currentAnimTimer<=40) {
        textureRec={32, 32, 32, 32};
    } else {
        textureRec={0, 32, 32, 32};
    }
    if (currentAnimTimer==0) {
        currentAnimTimer=animTimer;
    }


    if (Vector2Distance({newX, enemy.GetPosition().y}, jumpStart) <= 3.f){
        summonStep=SummonSteps::JumpUp;
        enemy.SetPosition(jumpStart);
        currentAnimTimer=animTimer;
    } else enemy.SetPosition({newX, enemy.GetPosition().y});

}

void MBSummonState::JumpUp(Enemy &enemy) {

    switch (jumpSubstep) {
        case 0:

            textureRec={32, 64, 32, 32};
            if (Vector2Distance(enemy.GetPosition(), highSpot)<=3.f){
                enemy.SetPosition(highSpot);
                lerpAlpha=0.f;
                ++jumpSubstep;
                currentAnimTimer=animTimer;
            } else {
                enemy.SetPosition(Vector2Lerp(jumpStart, highSpot, lerpAlpha));
                lerpAlpha+=0.05f;
            }
            break;
        case 1:
            textureRec={64, 64, 32, 32};
            if (Vector2Distance(enemy.GetPosition(), summonSpot)<=3.f){
                enemy.SetPosition(summonSpot);
                lerpAlpha=0.f;
                summonStep=SummonSteps::Summon;
                currentAnimTimer=animTimer;
            } else {
                enemy.SetPosition(Vector2Lerp(highSpot, summonSpot, lerpAlpha));
                lerpAlpha+=0.2f;
            }
            break;
    }

}

void MBSummonState::Summon(Enemy &enemy) {
    enemy.SetDirection(LEFT);
    enemy.SetInvulnerable(true);
    --currentAnimTimer;
    if (currentAnimTimer<=20){
        textureRec={64, 0, 32, 32};
    } else if (currentAnimTimer<=40) {
        textureRec={32, 0, 32, 32};
    } else {
        textureRec={0, 0, 32, 32};
    }
    if (currentAnimTimer==0) {
        currentAnimTimer=animTimer;
    }

    --summonTimer;
    if (summonTimer==1) {
        sceneManager->AddEnemy(std::make_unique<SpringHog>(spawn, EnemyLevel::Medium));
        sceneManager->AddEnemy(std::make_unique<SpringHog>(spawn2, EnemyLevel::Medium));
    }

    if (summonTimer<=0 && sceneManager->GetEnemies().size()==1) {
        currentAnimTimer=animTimer;
        enemy.SetInvulnerable(false);
        summonStep=SummonSteps::ReturnToGround;
    }
}

void MBSummonState::ReturnToGround(Enemy &enemy) {
    enemy.SetDirection(LEFT);
    switch (returnSubstep) {
        case 0:
            textureRec={32, 64, 32, 32};
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
            textureRec={64, 64, 32, 32};
            if (Vector2Distance(enemy.GetPosition(), jumpStart)<=3.f){
                enemy.SetPosition(jumpStart);
                lerpAlpha=0.f;
                summonStep=SummonSteps::Done;
                currentAnimTimer=animTimer;
            } else {
                enemy.SetPosition(Vector2Lerp(highSpot, jumpStart, lerpAlpha));
                lerpAlpha+=0.05f;
            }

            break;
    }

}
