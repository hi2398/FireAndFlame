#pragma once
#include "DialogueMananger.h"

class Scene {
public:
    Scene(std::string filepath);
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual ~Scene() = default;
    DialogueMananger &GetDialogueManager();
protected:
    DialogueMananger dialogueMananger;
private:

};


