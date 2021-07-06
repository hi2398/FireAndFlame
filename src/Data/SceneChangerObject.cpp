//
// Created by Ashty on 06.07.2021.
//

#include "SceneChangerObject.h"
#include "../Global.h"

SceneChangerObject::SceneChangerObject(Vector2 location) : Interactable(InteractableType::SceneChangeCollider){
    position = location;
    interactionZone = {position.x,position.y,128,128};
}

void SceneChangerObject::Interact(Actor &actor) {
    sceneManager->SetNextScene(std::make_unique<AreaOne>());
}

void SceneChangerObject::Update() {

}

void SceneChangerObject::Draw() {
    DrawRectangleRec(interactionZone,RED);
}
