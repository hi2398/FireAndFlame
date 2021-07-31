#pragma once
#include "raylib.h"
#include "../../Core/Interactable.h"

class SpearAttack: public Interactable{
public:
    SpearAttack(Vector2 position);
    void Interact(Actor &actor) override;
    void Update() override;
    void Draw() override;
    ~SpearAttack() override = default;

private:
    Texture2D texture;

    Vector2 spearPosition;
    Vector2 attackPoint;
    Vector2 moveTowardsPosition;

    float spearRotation = 0;
    bool damageActive = false;
    bool hasDamagedPlayer = false;
    bool fixAttack = false;
    int magnitude = 25; // speed of spear
    int prepareCounter = 120; // how long the spear targets the player until it flies towards the player
protected:

};