#pragma once
#include "raylib.h"
#include "../Global.h"
#include "../Core/Interactable.h"

class DialogueObject : public Interactable {
public:
    DialogueObject(std::string dialogFilepath,Vector2 position, Texture2D texture);
    void Interact(Actor& actor)override;
    void Draw() override;
    void Update() override;
    ~DialogueObject() override = default;;
private:
    std::string objFilepath;
    Vector2 objPosition;
    Texture2D objTexture;
protected:
};