//
// Created by Ashty on 08.07.2021.
//

#include "DialogueObject.h"

DialogueObject::DialogueObject(std::string dialogFilepath, Vector2 position, Texture2D texture) : Interactable(InteractableType::DialogObj){
    objFilepath = dialogFilepath;
    objPosition = position;
    objTexture = texture;
    interactionZone={position.x,position.y,static_cast<float>(texture.width),static_cast<float>(texture.height)};
}

void DialogueObject::Interact(Actor &actor) {
    hud->changeInteractable(true);
    if(IsKeyPressed(KEY_E) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_UP)){
        sceneManager->UpdateDialogInScene(objFilepath);
    }
}

void DialogueObject::Draw() {
    DrawTexture(objTexture,objPosition.x,objPosition.y,WHITE);
}

void DialogueObject::Update() {

}

DialogueObject::DialogueObject(std::string dialogFilepath, Vector2 position) : Interactable(InteractableType::DialogObj){
    objFilepath = dialogFilepath;
    objPosition = position;
    interactionZone={position.x,position.y,32,32};
}
