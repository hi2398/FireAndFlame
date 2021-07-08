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
    Rectangle dialogueBox = {300,400,700,300};
    std::string nextSent = "-";
    bool dialogueActive = {false};
};