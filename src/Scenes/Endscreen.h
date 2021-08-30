#pragma once
#include "../Core/Scene.h"

class Endscreen : public Scene{
public:
    Endscreen(SceneEnums lastScene);

    void Update() override;

    void Draw() override;

    ~Endscreen() override = default;

private:
    float endscreenCounter;
    std::string endText[17];
protected:

};