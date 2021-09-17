#include "PowerUp.h"

PowerUp::PowerUp(Vector2 location,PowerUpType type) : Interactable(InteractableType::Other){
    position = location;
    powerUpType = type;
    interactionZone = {position.x,position.y,16,16};
    texture = LoadTexture("assets/graphics/powerup_hearts.png");
    switch (powerUpType) {
        case PowerUpType::dash:
            thisFrame = {16, 0, 16, 16};
            break;
        case PowerUpType::wallJump:
            thisFrame = { 0, 16, 16, 16 };
            break;
        case PowerUpType::doubleJump:
            thisFrame = { 0, 0, 16, 16 };
            break;
        default:
            break;
    }
    destinationRec.x = position.x;
    destinationRec.y = position.y;
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

    //animation handling
    frameCounter++;
    
    if (frameCounter >= 10) {
        frameCounter = 0;
        destinationRec.width += difference;
        destinationRec.height += difference;
        destinationRec.x -= difference;
        destinationRec.y -= difference;
    }
    if (destinationRec.width >= 19) difference = -1;
    if (destinationRec.width <= 16) difference = 1;

}

void PowerUp::Draw() {
    DrawTexturePro(texture, thisFrame, destinationRec, { 0 }, 0, WHITE);
}

PowerUp::~PowerUp() {
    UnloadTexture(texture);
}
