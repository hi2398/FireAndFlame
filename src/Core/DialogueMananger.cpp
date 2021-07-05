#include "DialogueMananger.h"
#include <iostream>

DialogueMananger::DialogueMananger(std::string filePath) { // gets json file and saves it as dialogueFile
    std::ifstream dialogueFileTemp(filePath);
    dialogueFile = nlohmann::json::parse(dialogueFileTemp);
    dialogueFileTemp.close();
    StartDialogue();
}

void DialogueMananger::StartDialogue() {
    dialogueActive=false;
    for (auto sentence : dialogueFile["text"]){ // Adds all sentences from json file to queue
        sentences.push((std::string)sentence);
    }
    nextSent = sentences.front();
}

void DialogueMananger::UpdateDialogue() {
    const char *nextSentenceInQueue = nextSent.c_str();
    if(dialogueActive) {
        DrawRectangleRec(dialogueBox, RED);
        DrawText(nextSentenceInQueue, 320, 420, 30, BLUE);
    }
    if(IsKeyReleased(KEY_F)){
        NextSentence();
    }
}

void DialogueMananger::NextSentence() { // After Player pressed F this will happen
    if(!sentences.empty()) {
        nextSent = sentences.front();
        sentences.pop();
        //nextSentenceInQueue = nextSent.c_str();
    }else{
        dialogueActive=false;
    }
}
