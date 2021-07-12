#pragma once
#include "../Core/Scene.h"

class MainMenu : public Scene{
public:
    MainMenu();
    void Update() override;
    void Draw() override;
    ~MainMenu() override = default;


protected:

private:
    Rectangle button1 ={100,100,700,300};
};