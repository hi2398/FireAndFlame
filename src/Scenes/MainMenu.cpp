#include "MainMenu.h"
#include "../Global.h"
#include <iostream>
#include "../Scenes/NeutralArea.h"

MainMenu::MainMenu() {
    tilemap=std::make_unique<Tilemap>();
    playerCharacter->visible = false;
}

void MainMenu::Update() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    //playButton = {10, 30, 200, 100};
    //settingsButton = {, , (float)(screenWidth/5), (float)(screenHeight/8)};
    //creditsButton = {(float)(screenWidth/70), (float)(screenHeight/20 + 300), (float)(screenWidth/5), (float)(screenHeight/8)};
    //quitButton = {(float)(screenWidth/70), (float)(screenHeight/20 + 450), (float)(screenWidth/5), (float)(screenHeight/8)};
}

void MainMenu::Draw() {


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
