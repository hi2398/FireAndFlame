#include "MainMenu.h"
#include "../Global.h"
#include <iostream>
#include "../Scenes/NeutralArea.h"

MainMenu::MainMenu() {
    tilemap=std::make_unique<Tilemap>();
    playerCharacter->visible = false;
}

void MainMenu::Update() {

    switch(menuScreenStates){
        case MenuScreenStates::TitleScreen: ;
            break;
        case MenuScreenStates::LoadGameScreen: ;
            break;
        case MenuScreenStates::SettingsScreen: ;
            break;
        case MenuScreenStates::CreditsScreen: ;
            break;
        default: std::cout << "ERROR in MainMenu.cpp, Update()";
    }
}

void MainMenu::Draw() {


    switch(menuScreenStates){
        case MenuScreenStates::TitleScreen:
            DrawRectangle(30,60,300, 100, WHITE);
            DrawRectangle(30,200,300, 100, WHITE);
            DrawRectangle(30,340,300, 100, WHITE);
            DrawRectangle(30,480,300, 100, WHITE);
            break;
        case MenuScreenStates::LoadGameScreen: ;
            break;
        case MenuScreenStates::SettingsScreen: ;
            break;
        case MenuScreenStates::CreditsScreen: ;
            break;
        default: std::cout << "ERROR in MainMenu.cpp, Update()";
    }
}
