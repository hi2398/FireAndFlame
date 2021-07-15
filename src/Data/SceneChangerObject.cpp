#include "SceneChangerObject.h"
#include "../Global.h"
#include "../Scenes/NeutralArea.h"
#include "../Scenes/AreaOne.h"

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
    }
}

void SceneChangerObject::Update() {

}

void SceneChangerObject::Draw() {
    DrawRectangleRec(interactionZone,RED);
}
