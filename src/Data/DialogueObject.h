#pragma once
#include "raylib.h"
#include "../Global.h"
#include "../Core/Interactable.h"

class DialogueObject : public Interactable {
public:
    DialogueObject(std::string dialogFilepath,Vector2 position, bool personDialogue=false);
    DialogueObject(std::string dialogFilepath,Vector2 position, Texture2D texture, bool personDialogue = false);
    void Interact(Actor& actor)override;
    void Draw() override;
    void Update() override;
    void SetDialoguePath(std::string path);
    ~DialogueObject() override;
private:
    std::string objFilepath;
    Vector2 objPosition;
    Texture2D objTexture;
    bool personDialogue{ false };
protected:
};