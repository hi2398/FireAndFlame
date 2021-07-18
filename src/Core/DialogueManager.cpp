#include "DialogueManager.h"
#include "../Global.h"

void DialogueManager::UpdateDialogue(std::string filePath) {
    if(sentences.empty()&&nextSent!="-") {
        nextSent="-";
        dialogueActive=false;
        playerCharacter->SetPlayerDecreasingHealth(true);
        playerCharacter->ChangePlayerMovement(false);
    }else{
        playerCharacter->ChangePlayerMovement(true);
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
        DrawRectangleRec(dialogueBox, RED);
        if(nextSent.length()>60){
            fontSizeForDialogue = 23;
        }else fontSizeForDialogue = 30;
        DrawText(nextSentenceInQueue, 230, 535, fontSizeForDialogue, BLUE);
        DrawText("PRESS F TO CONTINUE", 820, 610, 15, BLUE);
    }
}