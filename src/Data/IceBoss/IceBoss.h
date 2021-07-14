#pragma once

#include "../../Core/Enemy.h"

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
    Texture2D texture;
    std::vector<Part> parts;

};


