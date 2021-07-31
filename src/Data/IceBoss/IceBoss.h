#pragma once
#include <random>

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

    explicit IceBoss(Vector2 location);
    void Update() override;
    void Draw() override;
    void ReceiveDamage(int damage) override;
    ~IceBoss() override = default;

    static bool Decide();
    static float SpeedMultiplier();
    Rectangle GetMeleeRange();
    static float GetRangedMinDistance();
    static float GetMovementSpeed();
    Texture2D GetMovingTexture();
protected:


private:
    static float constexpr normalMultiplier{1.f};
    static float constexpr aggressionMultiplier{1.2f};
    static const float* multiplier; //Don't change declaration order->initialization order matters
    Rectangle meleeRange{-16, 0, 64, 32};
    Texture2D texture;
    std::vector<Part> parts;
    std::shared_ptr<State> state;

    static constexpr float rangedMinDistance{128.f};
    static constexpr float movementSpeed{4.f};


};



