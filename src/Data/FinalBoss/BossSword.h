#pragma once

#include "../../Core/Interactable.h"

class BossSword : public Interactable{
public:
    BossSword(Vector2 position);
    void Interact(Actor &actor) override;
    void Update() override;
    void Draw() override;
    void ChangeTarget(Vector2 targetedPosition);
    ~BossSword() override = default;

private:
    Texture2D texture;
    int damageCounter = 60;
    bool hasDamagedPlayer = false;

    Vector2 targetPosition;
    Vector2 moveTowardsPosition;
    int magnitude = 50; // speed of energy attack
protected:
};
