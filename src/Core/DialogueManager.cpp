#include "DialogueManager.h"
#include "../Global.h"

void DialogueManager::UpdateDialogue(std::string filePath) {
    if(sentences.empty()&&nextSent!="-") {
        nextSent="-";
        dialogueActive=false;
        playerCharacter->SetPlayerDecreasingHealth(true);
        playerCharacter->BlockPlayerControls(false);
    }else{
        playerCharacter->BlockPlayerControls(true);
        playerCharacter->SetIsDashing(false); //so player cant open dialogue and dash away
        playerCharacter->SetPlayerDecreasingHealth(false);
        if (sentences.empty()) {
            std::ifstream dialogueFileTemp(filePath);
            nlohmann::json dialogueFile = nlohmann::json::parse(dialogueFileTemp);
            dialogueFileTemp.close();
            dialogueActive = true;
            for (auto sentence : dialogueFile["text"]) { // Adds all sentences from json file to queue
                sentences.push((std::string) sentence);
            }
            nextSent = sentences.front();
            sentences.pop();
        } else {
            nextSent = sentences.front();
            sentences.pop();
        }
    }
}

void DialogueManager::DrawDialogue() {
    const char *nextSentenceInQueue = nextSent.c_str();
    if(dialogueActive) {
        DrawTexture(dialogueBox,200,490,WHITE);
        if(nextSent.length()>60){
            fontSizeForDialogue = 22;
        }else fontSizeForDialogue = 28;
        DrawText(nextSentenceInQueue, 220, 550, fontSizeForDialogue, WHITE);
        DrawText("PRESS E OR GAMEPAD Y TO CONTINUE", 700, 610, 15, WHITE);
    }
}

DialogueManager::DialogueManager() {
    dialogueBox = LoadTexture("assets/graphics/GUI/DialogBox.png");
}
