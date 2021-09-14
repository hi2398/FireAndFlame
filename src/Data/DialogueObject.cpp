//
// Created by Ashty on 08.07.2021.
//

#include "DialogueObject.h"

DialogueObject::DialogueObject(std::string dialogFilepath, Vector2 position, Texture2D texture, bool personDialogue) : Interactable(InteractableType::DialogObj){
    this->personDialogue = personDialogue;
    objFilepath = dialogFilepath;
    objPosition = position;
    objTexture = texture;
    interactionZone={position.x,position.y,static_cast<float>(texture.width),static_cast<float>(texture.height)};
}

void DialogueObject::Interact(Actor &actor) {
    hud->changeInteractable(true);
    if(IsKeyPressed(KEY_E) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_UP)){
        sceneManager->UpdateDialogInScene(objFilepath, personDialogue);
    }
}

void DialogueObject::Draw() {
    DrawTexture(objTexture,objPosition.x,objPosition.y,WHITE);
}

void DialogueObject::Update() {

}

DialogueObject::DialogueObject(std::string dialogFilepath, Vector2 position, bool personDialogue) : Interactable(InteractableType::DialogObj){
    this->personDialogue = personDialogue;
    objFilepath = dialogFilepath;
    objPosition = position;
    interactionZone={position.x,position.y,32,32};
}

void DialogueObject::SetDialoguePath(std::string path) {
    objFilepath = path;
}

DialogueObject::~DialogueObject()
{
    UnloadTexture(objTexture);
}
