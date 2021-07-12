#include "MainMenu.h"
#include "../Global.h"
#include <iostream>
#define RAYGUI_IMPLEMENTATION
#include "../raygui.h"
#include "../Scenes/NeutralArea.h"

MainMenu::MainMenu() {
    tilemap=std::make_unique<Tilemap>();
    playerCharacter->visible = false;
}

void MainMenu::Update() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    playButton = {(float)(screenWidth/70), (float)(screenHeight/20), (float)(screenWidth/5), (float)(screenHeight/8)};
    settingsButton = {(float)(screenWidth/70), (float)(screenHeight/20 + 150), (float)(screenWidth/5), (float)(screenHeight/8)};
    creditsButton = {(float)(screenWidth/70), (float)(screenHeight/20 + 300), (float)(screenWidth/5), (float)(screenHeight/8)};
    quitButton = {(float)(screenWidth/70), (float)(screenHeight/20 + 450), (float)(screenWidth/5), (float)(screenHeight/8)};
}

void MainMenu::Draw() {


    switch(menuScreenStates){
        case MenuScreenStates::TitleScreen: ;
            if(GuiButton(playButton,"PLAY")){
                sceneManager->SetNextScene(std::make_unique<NeutralArea>());
            }
            if(GuiButton(settingsButton,"SETTINGS")){
                sceneManager->SetNextScene(std::make_unique<NeutralArea>());
            }
            if(GuiButton(creditsButton,"CREDITS")){
                sceneManager->SetNextScene(std::make_unique<NeutralArea>());
            }
            if(GuiButton(quitButton,"QUIT")){
                sceneManager->SetNextScene(std::make_unique<NeutralArea>());
            }
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
