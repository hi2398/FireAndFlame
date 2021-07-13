#include "MainMenu.h"
#include "../Global.h"
#include <iostream>
#include "NeutralArea.h"

MainMenu::MainMenu() {
    tilemap=std::make_unique<Tilemap>();
    playerCharacter->visible = false;

    gameTitlePicture = LoadTexture("assets/graphics/GUI/fireAndFlame.png");

    // Button Rectangle and Textures from Start Button
    playButton[0] = LoadTexture("assets/graphics/GUI/playButton1.png");
    playButton[1] = LoadTexture("assets/graphics/GUI/playButton2.png");
    playButton[2] = LoadTexture("assets/graphics/GUI/playButton3.png");
    playButtonRec = {30,60,(float)playButton[0].width,(float)playButton[0].height};

    // Button Rectangle and Textures from Settings Button
    settingsButton[0] = LoadTexture("assets/graphics/GUI/settingsButton1.png");
    settingsButton[1] = LoadTexture("assets/graphics/GUI/settingsButton2.png");
    settingsButton[2] = LoadTexture("assets/graphics/GUI/settingsButton3.png");
    settingsButtonRec = {30,200,(float)settingsButton[0].width,(float)settingsButton[0].height};

    // Button Rectangle and Textures from Credits Button
    creditsButton[0] = LoadTexture("assets/graphics/GUI/CreditsButton1.png");
    creditsButton[1] = LoadTexture("assets/graphics/GUI/CreditsButton2.png");
    creditsButton[2] = LoadTexture("assets/graphics/GUI/CreditsButton3.png");
    creditsButtonRec = {30,340,(float)creditsButton[0].width,(float)creditsButton[0].height};

    // Button Rectangle and Textures from Quit Button
    quitButton[0] = LoadTexture("assets/graphics/GUI/quitButton1.png");
    quitButton[1] = LoadTexture("assets/graphics/GUI/quitButton2.png");
    quitButton[2] = LoadTexture("assets/graphics/GUI/quitButton3.png");
    quitButtonRec = {30,480,(float)quitButton[0].width,(float)quitButton[0].height};

    // Button Rectangle and Textures from Back Button
    backButton[0] = LoadTexture("assets/graphics/GUI/backButton1.png");
    backButton[1] = LoadTexture("assets/graphics/GUI/backButton2.png");
    backButton[2] = LoadTexture("assets/graphics/GUI/backButton3.png");
    backButtonRec = {30, 600, (float)creditsButton[0].width, (float)creditsButton[0].height};

    for(int i = 0; i<10;i++){
        musicVolumeRecs[i] = {(float)(600+(60*i)),60,50,50};
        if(i<5){
            isMusicVolumeRecActive[i] = true;
            isSoundVolumeRecActive[i] = true;
        }else{
            isMusicVolumeRecActive[i] = false;
            isSoundVolumeRecActive[i] = false;
        }
        soundVolumeRecs[i] = {(float)(600+(60*i)),200,50,50};
    }
    fullscreenRec = {600,340,50,50};
}

void MainMenu::Update() {
    vMousePosition = sceneManager->GetVirtualMousePosition(); // Gets the virtual mouse position
    switch (menuScreenStates) {

        case MenuScreenStates::TitleScreen:

            if(CheckCollisionPointRec(vMousePosition,playButtonRec)){ // Handles the Button State of Play
                playButtonIndex = 1;
                if(IsMouseButtonDown(0)){
                    playButtonIndex = 2;
                }
                if(IsMouseButtonReleased(0)){
                    menuScreenStates = MenuScreenStates::LoadGameScreen;
                }
            }else{
                playButtonIndex = 0;
            }


            if(CheckCollisionPointRec(vMousePosition,settingsButtonRec)){ // Handles the Button State of Settings
                settingsButtonIndex = 1;
                if(IsMouseButtonDown(0)){
                    settingsButtonIndex = 2;
                }
                if(IsMouseButtonReleased(0)){
                    menuScreenStates = MenuScreenStates::SettingsScreen;
                }
            }else{
                settingsButtonIndex = 0;
            }


            if(CheckCollisionPointRec(vMousePosition,creditsButtonRec)){ // Handles the Button State of Credits
                creditsButtonIndex = 1;
                if(IsMouseButtonDown(0)){
                    creditsButtonIndex = 2;
                }
                if(IsMouseButtonReleased(0)){
                    menuScreenStates = MenuScreenStates::CreditsScreen;
                }
            }else{
                creditsButtonIndex = 0;
            }


            if(CheckCollisionPointRec(vMousePosition,quitButtonRec)){ // Handles the Button State of Quit
                quitButtonIndex = 1;
                if(IsMouseButtonDown(0)){
                    quitButtonIndex = 2;
                }
                if(IsMouseButtonReleased(0)){
                    CloseWindow();
                }
            }else{
                quitButtonIndex = 0;
            }

            break;


        case MenuScreenStates::LoadGameScreen:
            break;
        case MenuScreenStates::SettingsScreen:

            for(int i=0;i<10;i++) { // Changing Sound and Music Volume
                if (CheckCollisionPointRec(vMousePosition, musicVolumeRecs[i])) {
                    if(IsMouseButtonReleased(0)) {
                        musicVolume = i;
                        for(int e = 0; e < 10; e++){
                            if(e <= musicVolume){
                                isMusicVolumeRecActive[e] = true;
                            }else isMusicVolumeRecActive[e] = false;
                        }
                        break;
                    }
                }
                if (CheckCollisionPointRec(vMousePosition, soundVolumeRecs[i])) {
                    if(IsMouseButtonReleased(0)) {
                        soundVolume = i;
                        for(int e = 0; e < 10; e++){
                            if(e <= soundVolume){
                                isSoundVolumeRecActive[e] = true;
                            }else isSoundVolumeRecActive[e] = false;
                        }
                        break;
                    }
                }
            }


            if(CheckCollisionPointRec(vMousePosition,fullscreenRec)){
                if(IsMouseButtonReleased(0)){
                    isFullScreenActive = !isFullScreenActive;
                    if(isFullScreenActive && !IsWindowFullscreen()){
                        ToggleFullscreen();
                    }
                    if(!isFullScreenActive && IsWindowFullscreen()){
                        ToggleFullscreen();
                    }
                }
            }


            if(CheckCollisionPointRec(vMousePosition, backButtonRec)){
                backButtonIndex = 1;
                if(IsMouseButtonDown(0)){
                    backButtonIndex = 2;
                }
                if(IsMouseButtonReleased(0)){
                    menuScreenStates = MenuScreenStates::TitleScreen;
                }
            }else{
                backButtonIndex = 0;
            }


            break;
        case MenuScreenStates::CreditsScreen:

            if(CheckCollisionPointRec(vMousePosition, backButtonRec)){
                backButtonIndex = 1;
                if(IsMouseButtonDown(0)){
                    backButtonIndex = 2;
                }
                if(IsMouseButtonReleased(0)){
                    menuScreenStates = MenuScreenStates::TitleScreen;
                }
            }else{
                backButtonIndex = 0;
            }

            break;
    }
}

void MainMenu::Draw() {
    switch (menuScreenStates) {
        case MenuScreenStates::TitleScreen:

            DrawTexture(playButton[playButtonIndex],(float)playButtonRec.x,(float)playButtonRec.y,WHITE);
            DrawTexture(settingsButton[settingsButtonIndex],(float)settingsButtonRec.x,(float)settingsButtonRec.y,WHITE);
            DrawTexture(creditsButton[creditsButtonIndex],(float)creditsButtonRec.x,(float)creditsButtonRec.y,WHITE);
            DrawTexture(quitButton[quitButtonIndex],(float)quitButtonRec.x,(float)quitButtonRec.y,WHITE);
            DrawTexture(gameTitlePicture,600,30,WHITE);

            break;

        case MenuScreenStates::LoadGameScreen:

            break;

        case MenuScreenStates::SettingsScreen:

            DrawText("Music",30, 60, 50, WHITE);
            DrawText("Sound",30, 200, 50, WHITE);
            DrawText("Fullscreen",30, 340, 50, WHITE);

            for(int i = 0; i<10;i++){
                if(isMusicVolumeRecActive[i]){
                    DrawRectangleRec(musicVolumeRecs[i],BLUE);
                }else DrawRectangleRec(musicVolumeRecs[i],WHITE);
                if(isSoundVolumeRecActive[i]){
                    DrawRectangleRec(soundVolumeRecs[i],BLUE);
                }else DrawRectangleRec(soundVolumeRecs[i],WHITE);
            }

            if(isFullScreenActive){
                DrawRectangleRec(fullscreenRec,BLUE);
            }else DrawRectangleRec(fullscreenRec,WHITE);

            DrawTexture(backButton[backButtonIndex], (float)backButtonRec.x, (float)backButtonRec.y, WHITE);

            break;

        case MenuScreenStates::CreditsScreen:

            DrawText("Adrian Pfaff - Lead Programmer - Workflows \nAmar Civic - Programmer - Marketing \nRobin Günther - Programmer - UML-Diagrams \nPascal Hirt - Programmer - Sound and Music \nAykan Akgül - Lead Designer - World Design \nAndrea Preussner - Lead Artist - Animation",200,140,40,WHITE); // I am sorry
            DrawTexture(backButton[backButtonIndex], (float)backButtonRec.x, (float)backButtonRec.y, WHITE);

            break;
    }
}