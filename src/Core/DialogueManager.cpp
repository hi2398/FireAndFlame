#include "DialogueManager.h"
#include <iostream>

void DialogueManager::UpdateDialogue(std::string filePath) {
    if(sentences.empty()&&nextSent!="-") {
        nextSent="-";
        dialogueActive=false;
    }else{
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
        DrawText(nextSentenceInQueue, 320, 420, 30, BLUE);
    }
}