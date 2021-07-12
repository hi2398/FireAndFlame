#pragma once
#include "../Core/Scene.h"
#include "../raygui.h"

class MainMenu : public Scene{
public:
    MainMenu();
    void Update() override;
    void Draw() override;
    ~MainMenu() override = default;


protected:

private:

};