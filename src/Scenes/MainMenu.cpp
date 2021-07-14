#include "MainMenu.h"
#include "../Global.h"
#include <iostream>
#include "NeutralArea.h"

MainMenu::MainMenu() {
    tilemap=std::make_unique<Tilemap>();
    playerCharacter->visible = false; // Disables Player

    gameTitlePicture = LoadTexture("assets/graphics/GUI/fireAndFlame.png"); // The Title of our Game as a PNG Image, instead of Font only

    // Button Rectangle and Textures from Start Button in Title Screen
    playButton[0] = LoadTexture("assets/graphics/GUI/playButton1.png");
    playButton[1] = LoadTexture("assets/graphics/GUI/playButton2.png");
    playButton[2] = LoadTexture("assets/graphics/GUI/playButton3.png");
    playButtonRec = {30,60,(float)playButton[0].width,(float)playButton[0].height};

    // Button Rectangle and Textures from Settings Button in Title Screen
    settingsButton[0] = LoadTexture("assets/graphics/GUI/settingsButton1.png");
    settingsButton[1] = LoadTexture("assets/graphics/GUI/settingsButton2.png");
    settingsButton[2] = LoadTexture("assets/graphics/GUI/settingsButton3.png");
    settingsButtonRec = {30,200,(float)settingsButton[0].width,(float)settingsButton[0].height};

    // Button Rectangle and Textures from Credits Button in Title Screen
    creditsButton[0] = LoadTexture("assets/graphics/GUI/CreditsButton1.png");
    creditsButton[1] = LoadTexture("assets/graphics/GUI/CreditsButton2.png");
    creditsButton[2] = LoadTexture("assets/graphics/GUI/CreditsButton3.png");
    creditsButtonRec = {30,340,(float)creditsButton[0].width,(float)creditsButton[0].height};

    // Button Rectangle and Textures from Quit Button in Title Screen
    quitButton[0] = LoadTexture("assets/graphics/GUI/quitButton1.png");
    quitButton[1] = LoadTexture("assets/graphics/GUI/quitButton2.png");
    quitButton[2] = LoadTexture("assets/graphics/GUI/quitButton3.png");
    quitButtonRec = {30,480,(float)quitButton[0].width,(float)quitButton[0].height};


    // Buttons for Save and Load
    savegameTex1 = LoadTexture("assets/graphics/GUI/pic1.png");
    savegameTex2 = LoadTexture("assets/graphics/GUI/pic1.png");
    savegameTex3 = LoadTexture("assets/graphics/GUI/pic1.png");

    loadSave1Button[0] = LoadTexture("assets/graphics/GUI/loadsave11.png");
    loadSave1Button[1] = LoadTexture("assets/graphics/GUI/loadsave12.png");
    loadSave1Button[2] = LoadTexture("assets/graphics/GUI/loadsave13.png");
    loadSave1ButtonRec = {50,480,(float)loadSave1Button[0].width,(float)loadSave1Button[0].height};

    loadSave2Button[0] = LoadTexture("assets/graphics/GUI/loadsave21.png");
    loadSave2Button[1] = LoadTexture("assets/graphics/GUI/loadsave22.png");
    loadSave2Button[2] = LoadTexture("assets/graphics/GUI/loadsave23.png");
    loadSave2ButtonRec = {460,480,(float)loadSave2Button[0].width,(float)loadSave2Button[0].height};

    loadSave3Button[0] = LoadTexture("assets/graphics/GUI/loadsave31.png");
    loadSave3Button[1] = LoadTexture("assets/graphics/GUI/loadsave32.png");
    loadSave3Button[2] = LoadTexture("assets/graphics/GUI/loadsave33.png");
    loadSave3ButtonRec = {870,480,(float)loadSave3Button[0].width,(float)loadSave3Button[0].height};

    deleteSave1Button[0] = LoadTexture("assets/graphics/GUI/resetgame1.png");
    deleteSave1Button[1] = LoadTexture("assets/graphics/GUI/resetgame2.png");
    deleteSave1Button[2] = LoadTexture("assets/graphics/GUI/resetgame3.png");
    deleteSave1ButtonRec = {87.5,40,275,75};

    deleteSave2Button[0] = LoadTexture("assets/graphics/GUI/resetgame1.png");
    deleteSave2Button[1] = LoadTexture("assets/graphics/GUI/resetgame2.png");
    deleteSave2Button[2] = LoadTexture("assets/graphics/GUI/resetgame3.png");
    deleteSave2ButtonRec = {496,40,275,75};

    deleteSave3Button[0] = LoadTexture("assets/graphics/GUI/resetgame1.png");
    deleteSave3Button[1] = LoadTexture("assets/graphics/GUI/resetgame2.png");
    deleteSave3Button[2] = LoadTexture("assets/graphics/GUI/resetgame3.png");
    deleteSave3ButtonRec = {905.5,40,275,75};


    // Button Rectangle and Textures from Back Button in Settings and Credits Screen
    backButton[0] = LoadTexture("assets/graphics/GUI/backButton1.png");
    backButton[1] = LoadTexture("assets/graphics/GUI/backButton2.png");
    backButton[2] = LoadTexture("assets/graphics/GUI/backButton3.png");
    backButtonRec = {30, 600, (float)creditsButton[0].width, (float)creditsButton[0].height};

    for(int i = 0; i<10;i++){ // Activating the Sound and Music Rectangles TODO(temp only rework after save and load is finished)
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

            if(CheckCollisionPointRec(vMousePosition, deleteSave1ButtonRec)){
                deleteSave1ButtonIndex = 1;
                if(IsMouseButtonDown(0)){
                    deleteSave1ButtonIndex = 2;
                }
                if(IsMouseButtonReleased(0)){
                    // delete save 1
                }
            }else{
                deleteSave1ButtonIndex = 0;
            }

            if(CheckCollisionPointRec(vMousePosition, deleteSave2ButtonRec)){
                deleteSave2ButtonIndex = 1;
                if(IsMouseButtonDown(0)){
                    deleteSave2ButtonIndex = 2;
                }
                if(IsMouseButtonReleased(0)){
                    // delete save 2
                }
            }else{
                deleteSave2ButtonIndex = 0;
            }

            if(CheckCollisionPointRec(vMousePosition, deleteSave3ButtonRec)){
                deleteSave3ButtonIndex = 1;
                if(IsMouseButtonDown(0)){
                    deleteSave3ButtonIndex = 2;
                }
                if(IsMouseButtonReleased(0)){
                    // delete save 3
                }
            }else{
                deleteSave3ButtonIndex = 0;
            }

            if(CheckCollisionPointRec(vMousePosition, loadSave1ButtonRec)){
                loadSave1ButtonIndex = 1;
                if(IsMouseButtonDown(0)){
                    loadSave1ButtonIndex = 2;
                }
                if(IsMouseButtonReleased(0)){
                    sceneManager->SetNextScene(std::make_unique<NeutralArea>());
                }
            }else{
                loadSave1ButtonIndex = 0;
            }

            if(CheckCollisionPointRec(vMousePosition, loadSave2ButtonRec)){
                loadSave2ButtonIndex = 1;
                if(IsMouseButtonDown(0)){
                    loadSave2ButtonIndex = 2;
                }
                if(IsMouseButtonReleased(0)){
                    sceneManager->SetNextScene(std::make_unique<NeutralArea>());
                }
            }else{
                loadSave2ButtonIndex = 0;
            }

            if(CheckCollisionPointRec(vMousePosition, loadSave3ButtonRec)){
                loadSave3ButtonIndex = 1;
                if(IsMouseButtonDown(0)){
                    loadSave3ButtonIndex = 2;
                }
                if(IsMouseButtonReleased(0)){
                    sceneManager->SetNextScene(std::make_unique<NeutralArea>());
                }
            }else{
                loadSave3ButtonIndex = 0;
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

            DrawTexture(loadSave1Button[loadSave1ButtonIndex],loadSave1ButtonRec.x,loadSave1ButtonRec.y,WHITE);
            DrawTexture(loadSave2Button[loadSave2ButtonIndex],loadSave2ButtonRec.x,loadSave2ButtonRec.y,WHITE);
            DrawTexture(loadSave3Button[loadSave3ButtonIndex],loadSave3ButtonRec.x,loadSave3ButtonRec.y,WHITE);

            DrawTexture(savegameTex1,75,150,WHITE);
            DrawTexture(savegameTex2,485,150,WHITE);
            DrawTexture(savegameTex3,895,150,WHITE);

            DrawTexture(deleteSave1Button[deleteSave1ButtonIndex],deleteSave1ButtonRec.x,deleteSave1ButtonRec.y,WHITE);
            DrawTexture(deleteSave2Button[deleteSave2ButtonIndex],deleteSave2ButtonRec.x,deleteSave2ButtonRec.y,WHITE);
            DrawTexture(deleteSave3Button[deleteSave3ButtonIndex],deleteSave3ButtonRec.x,deleteSave3ButtonRec.y,WHITE);

            DrawTexture(backButton[backButtonIndex], (float)backButtonRec.x, (float)backButtonRec.y, WHITE);
            break;

        case MenuScreenStates::SettingsScreen:

            DrawText("Music",30, 60, 50, WHITE);
            DrawText("Sound",30, 200, 50, WHITE);
            DrawText("Fullscreen",30, 340, 50, WHITE);

            for(int i = 0; i<10;i++){ // Drawing Sound and Music Recs in Settings
                if(isMusicVolumeRecActive[i]){
                    if(musicVolume == 0 && i == 0){
                        DrawRectangleRec(musicVolumeRecs[i],RED);
                    }
                    else DrawRectangleRec(musicVolumeRecs[i],BLUE);
                }else DrawRectangleRec(musicVolumeRecs[i],WHITE);
                if(isSoundVolumeRecActive[i]){
                    if(soundVolume == 0 && i == 0){
                        DrawRectangleRec(soundVolumeRecs[i],RED);
                    } else DrawRectangleRec(soundVolumeRecs[i],BLUE);
                }else DrawRectangleRec(soundVolumeRecs[i],WHITE);
            }

            if(isFullScreenActive){ // Fullscreen Rec
                DrawRectangleRec(fullscreenRec,BLUE);
            }else DrawRectangleRec(fullscreenRec,WHITE);

            DrawTexture(backButton[backButtonIndex], (float)backButtonRec.x, (float)backButtonRec.y, WHITE);

            break;

        case MenuScreenStates::CreditsScreen: // Drawings Credits

            DrawText("Adrian Pfaff - Lead Programmer - Workflows \nAmar Civic - Programmer - Marketing \nRobin Günther - Programmer - UML-Diagrams \nPascal Hirt - Programmer - Sound and Music \nAykan Akgül - Lead Designer - World Design \nAndrea Preussner - Lead Artist - Animation",200,140,40,WHITE); // I am sorry
            DrawTexture(backButton[backButtonIndex], (float)backButtonRec.x, (float)backButtonRec.y, WHITE);

            break;
    }
}