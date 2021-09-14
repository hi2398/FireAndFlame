#pragma once
#include "raylib.h"
#include "../Global.h"
#include "../Core/Interactable.h"

enum class PowerUpType {def,dash,wallJump,doubleJump};

class PowerUp : public Interactable{
public:
    PowerUp(Vector2 location={0, 0}, PowerUpType poType = PowerUpType::def);
    void Interact(Actor& actor)override;
    void Update() override;
    void Draw() override;
    ~PowerUp() override;
private:
    PowerUpType powerUpType;
    Texture2D texture;
    Rectangle thisFrame = {0,0,16,16};
    Rectangle destinationRec = { 0,0,16,16 };
    int difference = 1;
    int frameCounter = 0;
    bool dialogueActive = false;
    bool isGamepadActive = false;
protected:
};
