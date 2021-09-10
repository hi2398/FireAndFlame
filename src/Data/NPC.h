#pragma once
#include "raylib.h"
#include "../Global.h"
#include "DialogueObject.h"

enum class NPCType{one,two,three,four,five};

class NPC : public DialogueObject{
public:
    NPC(std::string dialogFilepath, Vector2 position, NPCType npcType,std::string gamepadDialogue);
    void Update() override;
    void Draw() override;
    ~NPC() = default;
private:
    std::string objFilepath;
    std::string gamepadObjFilepath;
    Vector2 objPosition;
    Texture2D objTexture;
    int counter = 15;
    NPCType type = NPCType::one;
    Rectangle drawBox = {0,0,32,32};
protected:
};