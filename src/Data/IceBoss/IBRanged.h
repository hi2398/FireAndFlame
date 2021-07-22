#pragma once

#include "../../Core/State.h"

class IBRanged : public State{
public:
    explicit IBRanged(Vector2 startLocation);

    std::shared_ptr <State> Update(Actor &actor) override;

    void Draw(Actor &actor) override;

    ~IBRanged() override = default;

protected:


private:
    int animTimer{90};
    Vector2 targetLocation{29*32, 36*32};
    Vector2 startLocation{};
    Vector2 barrelPos;
    Texture2D barrel;

};


