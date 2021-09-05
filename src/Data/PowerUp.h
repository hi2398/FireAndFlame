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
    bool dialogueActive = false;
protected:
};
