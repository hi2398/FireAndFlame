#pragma once
#include "raylib.h"
#include "../Global.h"
#include "../Core/Interactable.h"

class DialogObject : public Interactable {
public:
    DialogObject(std::string dialogFilepath,Vector2 position, Texture2D texture);
    void Interact(Actor& actor)override;
    void Draw() override;
    void Update() override;
    ~DialogObject() override = default;;
private:
    std::string objFilepath;
    Vector2 objPosition;
    Texture2D objTexture;
protected:
};