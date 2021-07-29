#pragma once
#include "../Core/Scene.h"

class Endscreen : public Scene{
public:
    Endscreen();

    void Update() override;

    void Draw() override;

    ~Endscreen() override = default;

private:
    float endscreenCounter = 0.0f;
    std::string endText[17];
protected:

};