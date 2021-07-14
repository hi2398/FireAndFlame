#pragma once

#include "../../Core/Enemy.h"
#include "../../Core/State.h"

struct Part {
    Vector2 offset;
    float rotation;
    Texture2D texture;
    int hitPoints;
};

class IceBoss : public Enemy {
public:

    IceBoss(Vector2 location);
    void Update() override;
    void Draw() override;
    void ReceiveDamage(int damage) override;
    ~IceBoss() override = default;

protected:


private:
    float normalMultiplier{1.f};
    float aggressionMultiplier{1.2f};
    float& multiplier; //Don't change declaration order->initialization order matters
    Texture2D texture;
    std::vector<Part> parts;
    std::shared_ptr<State> state;

};


