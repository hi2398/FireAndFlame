#include "DialogueMananger.h"

DialogueMananger::DialogueMananger(std::string filePath) { // gets json file and saves it as dialogueFile
    std::ifstream dialogueFileTemp(filePath);
    dialogueFile = nlohmann::json::parse(dialogueFileTemp);
    dialogueFileTemp.close();

    StartDialogue();
}

void DialogueMananger::StartDialogue() {
    //Start Dialogue State
    for (auto const &sentence : dialogueFile["text"]){ // Adds all sentences from json file to queue
        sentences.push((std::string)sentence);
    }
    std::string nextSent = sentences.front();
    sentences.pop();
    nextSentenceInQue = nextSent.c_str();
}

void DialogueMananger::UpdateDialogue() {
    DrawRectangleRec(dialogueBox, RED);
    DrawText(nextSentenceInQue,320,420,10,BLUE);
}

void DialogueMananger::NextSentence() { // After Player pressed F this will happen
    if(!sentences.empty()) {
        std::string nextSent = sentences.front();
        sentences.pop();
        nextSentenceInQue = nextSent.c_str();
    }else{
        //End Dialogue State
    }
}
