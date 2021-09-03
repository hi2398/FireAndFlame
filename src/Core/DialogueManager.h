#pragma once
#include <string>
#include <queue>
#include "../json.hpp"
#include <fstream>
#include "raylib.h"

class DialogueManager {
public:
    DialogueManager();
    bool GetDialogueActive();
    void UpdateDialogue(std::string filePath);
    void DrawDialogue();
protected:
private:
    std::queue<std::string> sentences;
    Texture2D dialogueBox;
    int fontSizeForDialogue = 30;
    std::string nextSent = "-";
    bool dialogueActive = {false};
};