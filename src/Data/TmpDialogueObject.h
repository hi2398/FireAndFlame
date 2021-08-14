#pragma once
#include "raylib.h"
#include "../Global.h"
#include "../Core/Interactable.h"

class TmpDialogueObject : public Interactable {
public:
    TmpDialogueObject(std::string dialogFilepath, Vector2 position, Texture2D texture);
    void Interact(Actor& actor)override;
    void Draw() override;
    void Update() override;
    ~TmpDialogueObject() override = default;;
private:
    std::string objFilepath;
    Vector2 objPosition;
    Texture2D objTexture;
protected:
    bool textActivated{ false };
};