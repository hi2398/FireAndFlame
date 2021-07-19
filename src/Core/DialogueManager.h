#pragma once
#include <string>
#include <queue>
#include "../json.hpp"
#include <fstream>
#include "raylib.h"

class DialogueManager {
public:
    void UpdateDialogue(std::string filePath);
    void DrawDialogue();
protected:
private:
    std::queue<std::string> sentences;
    Rectangle dialogueBox = {200,490,900,150};
    int fontSizeForDialogue = 30;
    std::string nextSent = "-";
    bool dialogueActive = {false};
};