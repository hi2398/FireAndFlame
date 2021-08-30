#pragma once

#include "../../Core/EState.h"

class IceBoss;

enum class RangedStep{WindUp, Throw, JumpDown};

class IBRanged : public EState{
public:
    explicit IBRanged(Vector2 startLocation, Enemy &enemy);
    std::shared_ptr <EState> Update(Enemy &enemy) override;

    void Draw(Enemy &enemy) override;

    ~IBRanged() override = default;

protected:


private:
    void WindUp(IceBoss* iceBoss);
    void JumpDown(IceBoss* iceBoss);
    void ThrowBarrel(IceBoss* iceBoss);

    RangedStep rangedStep{RangedStep::WindUp};
    int animTimer{90};
    Vector2 targetLocation;
    Vector2 startLocation{};
    Vector2 barrelPos;
    Texture2D barrel;
    bool jumpStarted{false};
    int jumpTimer{60};
    int windUpTimer{60};
    const Vector2 jumpEnd{29*32, 36*32};
    Rectangle texRec;
};


