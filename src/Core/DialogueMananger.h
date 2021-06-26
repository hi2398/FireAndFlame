#pragma once
#include <string>
#include <queue>
#include "../json.hpp"
#include <fstream>
#include "raylib.h"

class DialogueMananger {
public:
    DialogueMananger(std::string filePath);
    void UpdateDialogue();
    void NextSentence();
protected:
private:
    void StartDialogue();
    std::queue<std::string> sentences;
    nlohmann::json dialogueFile;
    Rectangle dialogueBox = {300,400,700,300};
    const char *nextSentenceInQue;
};
