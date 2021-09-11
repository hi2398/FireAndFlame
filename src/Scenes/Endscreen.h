#pragma once
#include "../Core/Scene.h"

class Endscreen : public Scene{
public:
    Endscreen(SceneEnums lastScene);

    void Update() override;

    void Draw() override;

    ~Endscreen() override;

private:
    float endscreenCounter;
    std::string endText[19];
    Music track;
protected:

};