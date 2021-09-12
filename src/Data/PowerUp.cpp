#include "PowerUp.h"

PowerUp::PowerUp(Vector2 location,PowerUpType type) : Interactable(InteractableType::Other){
    position = location;
    powerUpType = type;
    interactionZone = {position.x,position.y,16,16};
    switch (powerUpType) {
        case PowerUpType::dash:
            texture = LoadTexture("assets/graphics/dashUpgrade.png");
            break;
        case PowerUpType::wallJump:
            texture = LoadTexture("assets/graphics/wallJumpUpgrade.png");
            break;
        case PowerUpType::doubleJump:
            texture = LoadTexture("assets/graphics/doubleJumpUpgrade.png");
            break;
        default:
            break;
    }
}

void PowerUp::Interact(Actor &actor) {
    switch (powerUpType) {
        case PowerUpType::dash:
            if(!dialogueActive) {
                playerCharacter->SetUnlockedAbilityLevel(AbilitiesUnlocked::Dash);
                if(!isGamepadActive){
                    sceneManager->UpdateDialogInScene("assets/Dialogues/dashUpgrade.json", false);
                }else {sceneManager->UpdateDialogInScene("assets/Dialogues/dashUpgradeGamepad.json", false);}
                dialogueActive = true;
            }
            break;
        case PowerUpType::wallJump:
            if(!dialogueActive) {
                playerCharacter->SetUnlockedAbilityLevel(AbilitiesUnlocked::Walljump);
                if(!isGamepadActive){
                    sceneManager->UpdateDialogInScene("assets/Dialogues/wallJumpUpgrade.json", false);
                }else {sceneManager->UpdateDialogInScene("assets/Dialogues/wallJumpUpgradeGamepad.json", false);}
                dialogueActive = true;
            }
            break;
        case PowerUpType::doubleJump:
            if(!dialogueActive) {
                playerCharacter->SetUnlockedAbilityLevel(AbilitiesUnlocked::Doublejump);
                if(!isGamepadActive){
                    sceneManager->UpdateDialogInScene("assets/Dialogues/doubleJump.json", false);
                }else {sceneManager->UpdateDialogInScene("assets/Dialogues/doubleJumpGamepad.json", false);}
                dialogueActive = true;
            }
            break;
        default:
            break;
    }
}

void PowerUp::Update() {
    if(IsGamepadAvailable(0)){
        isGamepadActive = true;
    }else{
        isGamepadActive = false;
    }
    if(dialogueActive){
        if(!sceneManager->GetActiveScene()->GetDialogueManager().GetDialogueActive()){
            markedDestroy = true;
        }
    }
    if((IsKeyPressed(KEY_E) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_UP))&& CheckCollisionRecs(playerCharacter->playerHitbox,interactionZone)){
        sceneManager->UpdateDialogInScene("assets/Dialogues/TutorialSign.json", false);
    }
}

void PowerUp::Draw() {
    DrawTexture(texture,position.x,position.y,WHITE);
}

PowerUp::~PowerUp() {

}
