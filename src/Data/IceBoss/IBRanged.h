#pragma once

#include "../../Core/EState.h"

class IBRanged : public EState{
public:
    explicit IBRanged(Vector2 startLocation, Enemy &enemy);
    std::shared_ptr <EState> Update(Enemy &enemy) override;

    void Draw(Enemy &enemy) override;

    ~IBRanged() override = default;

protected:


private:
    int animTimer{90};
    Vector2 targetLocation;
    Vector2 startLocation{};
    Vector2 barrelPos;
    Texture2D barrel;
    bool jumpStarted{false};
    int jumpTimer{60};
    const Vector2 jumpEnd{29*32, 36*32};
    Rectangle texRec;
};


