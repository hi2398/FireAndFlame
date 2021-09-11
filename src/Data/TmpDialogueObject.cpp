
#include "TmpDialogueObject.h"

TmpDialogueObject::TmpDialogueObject(std::string dialogFilepath, Vector2 position, Texture2D texture) : Interactable(InteractableType::TmpDialogObj) {
    objFilepath = dialogFilepath;
    objPosition = position;
    objTexture = texture;
    interactionZone = { position.x,position.y,static_cast<float>(texture.width),static_cast<float>(texture.height) };
}

void TmpDialogueObject::Interact(Actor& actor) {
    hud->changeInteractable(true);

    if (!textActivated) {
        sceneManager->UpdateDialogInScene(objFilepath);
        textActivated = true;
    }
    else {
		if (IsKeyPressed(KEY_E) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_UP)) {
			sceneManager->UpdateDialogInScene(objFilepath);
		}
    }
}


void TmpDialogueObject::Update() {

}