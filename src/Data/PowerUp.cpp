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
                sceneManager->UpdateDialogInScene("assets/Dialogues/TutorialSign.json");
                dialogueActive = true;
            }
            break;
        case PowerUpType::wallJump:
            if(!dialogueActive) {
                playerCharacter->SetUnlockedAbilityLevel(AbilitiesUnlocked::Walljump);
                sceneManager->UpdateDialogInScene("assets/Dialogues/TutorialSign.json");
                dialogueActive = true;
            }
            break;
        case PowerUpType::doubleJump:
            if(!dialogueActive) {
                playerCharacter->SetUnlockedAbilityLevel(AbilitiesUnlocked::Doublejump);
                sceneManager->UpdateDialogInScene("assets/Dialogues/TutorialSign.json");
                dialogueActive = true;
            }
            break;
        default:
            break;
    }
}

void PowerUp::Update() {
    if(dialogueActive){
        if(!sceneManager->GetActiveScene()->GetDialogueManager().GetDialogueActive()){
            markedDestroy = true;
        }
    }
    if((IsKeyPressed(KEY_E) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_UP))&& CheckCollisionRecs(playerCharacter->playerHitbox,interactionZone)){
        sceneManager->UpdateDialogInScene("assets/Dialogues/TutorialSign.json");
    }
}

void PowerUp::Draw() {
    DrawTexture(texture,position.x,position.y,WHITE);
}

PowerUp::~PowerUp() {

}
