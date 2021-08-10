#include "SceneChangerObject.h"
#include "../Global.h"
#include "../Scenes/NeutralArea.h"
#include "../Scenes/AreaOne.h"
#include "../Scenes/AreaTwo.h"
#include "../Scenes/AreaThree.h"
#include "../Scenes/IceBossScene.h"
#include "../Scenes/FinalBoss.h"
#include "../Scenes/MinerBossScene.h"
#include "../Scenes/TraitorBossScene.h"

SceneChangerObject::SceneChangerObject(Vector2 location, SceneEnums sceneEnum) : Interactable(InteractableType::SceneChangeCollider){
    position = location;
    chosenScene = sceneEnum;
    interactionZone = {position.x,position.y,128,128};
}

void SceneChangerObject::Interact(Actor &actor) {
    switch(chosenScene){
        case SceneEnums::NeutralArea :
            sceneManager->SetNextScene(std::make_unique<NeutralArea>());
            break;
        case SceneEnums::AreaOne :
            sceneManager->SetNextScene(std::make_unique<AreaOne>());
            break;
        case SceneEnums::IceBoss :
            sceneManager->SetNextScene(std::make_unique<IceBossScene>());
            break;
        case SceneEnums::AreaTwo :
            sceneManager->SetNextScene(std::make_unique<AreaTwo>());
            break;
        case SceneEnums::FinalBoss :
            sceneManager->SetNextScene(std::make_unique<FinalBoss>());
            break;
        case SceneEnums::MinerBoss :
            sceneManager->SetNextScene(std::make_unique<MinerBossScene>());
            break;
        case SceneEnums::TraitorBoss :
            sceneManager->SetNextScene(std::make_unique<TraitorBossScene>());
            break;
    }
}

void SceneChangerObject::Update() {

}

void SceneChangerObject::Draw() {
    DrawRectangleRec(interactionZone,RED);
}
