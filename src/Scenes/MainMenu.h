#pragma once
#include "../Core/Scene.h"

class MainMenu : public Scene{
public:
    void Update() override;
    void Draw() override;
    ~MainMenu() override = default;


protected:

private:
    Rectangle ground = { -1000, 40, 2100, 300};
};


