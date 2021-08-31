#include "MainMenu.h"
#include "../Global.h"
#include <iostream>
#include "Tutorial.h"

MainMenu::MainMenu(SceneEnums lastScene) : Scene(SceneEnums::Default) {
    this->lastScene = lastScene;
    tilemap=std::make_unique<Tilemap>();
    playerCharacter->active = false; // Disables Player

    mainMenuBackground = LoadTexture("assets/graphics/GUI/fireAndFlame.png");
    gameTitlePicture = LoadTexture("assets/graphics/GUI/fireAndFlameLogo.png");// The Title of our Game as a PNG Image, instead of Font only

    // Button Rectangle and Textures from Start Button in Title Screen
    playButton = LoadTexture("assets/graphics/GUI/loadGame.png");
    playButtonRec = {30,60,(float)playButton.width,(float)playButton.height};

    // Button Rectangle and Textures from Settings Button in Title Screen
    settingsButton = LoadTexture("assets/graphics/GUI/settingsButton.png");
    settingsButtonRec = {30,200,(float)settingsButton.width,(float)settingsButton.height};

    // Button Rectangle and Textures from Credits Button in Title Screen
    creditsButton = LoadTexture("assets/graphics/GUI/creditsButton.png");
    creditsButtonRec = {30,340,(float)creditsButton.width,(float)creditsButton.height};

    // Button Rectangle and Textures from Quit Button in Title Screen
    quitButton = LoadTexture("assets/graphics/GUI/quitButton.png");
    quitButtonRec = {30,480,(float)quitButton.width,(float)quitButton.height};


    // Buttons for Save and Load
    savegameTex1 = LoadTexture("assets/graphics/GUI/pic1.png");
    savegameTex2 = LoadTexture("assets/graphics/GUI/pic1.png");
    savegameTex3 = LoadTexture("assets/graphics/GUI/pic1.png");

    loadSave1Button = LoadTexture("assets/graphics/GUI/loadsave.png");
    loadSave1ButtonRec = {50,480,(float)loadSave1Button.width,(float)loadSave1Button.height};

    loadSave2Button = LoadTexture("assets/graphics/GUI/loadsave.png");
    loadSave2ButtonRec = {460,480,(float)loadSave2Button.width,(float)loadSave2Button.height};

    loadSave3Button = LoadTexture("assets/graphics/GUI/loadsave.png");
    loadSave3ButtonRec = {870,480,(float)loadSave3Button.width,(float)loadSave3Button.height};

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
    backButton = LoadTexture("assets/graphics/GUI/backButton.png");

    backButtonRec = {30, 590, (float)creditsButton.width, (float)creditsButton.height};

    emptyHearth = LoadTexture("assets/graphics/GUI/emptyHearth.png");
    orangeHearth = LoadTexture("assets/graphics/GUI/orangeHearth.png");
    redHearth = LoadTexture("assets/graphics/GUI/redHearth.png");

    musicText = LoadTexture("assets/graphics/GUI/musicText.png");

    for(int i = 0; i<10;i++){ // Activating the Sound and Music Rectangles TODO(temp only rework after save and load is finished)
        musicVolumeRecs[i] = {(float)(600+(60*i)),60,50,50};
        soundVolumeRecs[i] = {(float)(600+(60*i)),200,50,50};
    }
    UpdateMusicAndSoundVolume();
    fullscreenRec = {600,340,50,50};

    //load soundtrack
    soundManager->PlayTrack(TRACK::MENU_TRACK);
}

void MainMenu::Update() {
    soundManager->UpdateTrack(TRACK::MENU_TRACK);
    vMousePosition = sceneManager->GetVirtualMousePosition(); // Gets the virtual mouse position

    switch (menuScreenStates) {

        case MenuScreenStates::TitleScreen:

            if(CheckCollisionPointRec(vMousePosition,playButtonRec) || (controllerStates == ControllerMainMenuStates::PlayGameButton && controllerActive)){ // Handles the Button State of Play
                playButtonColor = {200,200,200,255};
                if(IsMouseButtonDown(0)|| (IsGamepadButtonPressed(0,GAMEPAD_BUTTON_RIGHT_FACE_DOWN)&& controllerActive)&& controllerStates == ControllerMainMenuStates::PlayGameButton){
                    playButtonColor = {100,100,100,255};
                }
                if(IsMouseButtonReleased(0) || (IsGamepadButtonReleased(0,GAMEPAD_BUTTON_RIGHT_FACE_DOWN)&& controllerActive)&& controllerStates == ControllerMainMenuStates::PlayGameButton){
                    controllerStates = ControllerMainMenuStates::LoadGame1;
                    menuScreenStates = MenuScreenStates::LoadGameScreen;
                }
            }else{
                playButtonColor = {255,255,255,255};
            }


            if(CheckCollisionPointRec(vMousePosition,settingsButtonRec) || controllerStates == ControllerMainMenuStates::SettingsButton){ // Handles the Button State of Settings
                settingsColor = {200,200,200,255};
                if(IsMouseButtonDown(0) || (IsGamepadButtonPressed(0,GAMEPAD_BUTTON_RIGHT_FACE_DOWN) && controllerStates == ControllerMainMenuStates::SettingsButton)){
                    settingsColor = {100,100,100,255};
                }
                if(IsMouseButtonReleased(0) || (IsGamepadButtonReleased(0,GAMEPAD_BUTTON_RIGHT_FACE_DOWN) && controllerStates == ControllerMainMenuStates::SettingsButton)){
                    controllerStates = ControllerMainMenuStates::ChangeMusic;
                    menuScreenStates = MenuScreenStates::SettingsScreen;
                }
            }else{
                settingsColor = {255,255,255,255};
            }


            if(CheckCollisionPointRec(vMousePosition,creditsButtonRec) || controllerStates == ControllerMainMenuStates::CreditsButton){ // Handles the Button State of Credits
                creditsColor = {200,200,200,255};
                if(IsMouseButtonDown(0) || (IsGamepadButtonPressed(0,GAMEPAD_BUTTON_RIGHT_FACE_DOWN) && controllerStates == ControllerMainMenuStates::CreditsButton)){
                    creditsColor = {100,100,100,255};
                }
                if(IsMouseButtonReleased(0) || (IsGamepadButtonReleased(0,GAMEPAD_BUTTON_RIGHT_FACE_DOWN) && controllerStates == ControllerMainMenuStates::CreditsButton)){
                    menuScreenStates = MenuScreenStates::CreditsScreen;
                }
            }else{
                creditsColor = {255,255,255,255};
            }


            if(CheckCollisionPointRec(vMousePosition,quitButtonRec) || controllerStates == ControllerMainMenuStates::QuitButton){ // Handles the Button State of Quit
                quitColor = {200,200,200,255};
                if(IsMouseButtonDown(0) || (IsGamepadButtonPressed(0,GAMEPAD_BUTTON_RIGHT_FACE_DOWN) && controllerStates == ControllerMainMenuStates::QuitButton)){
                    quitColor = {100,100,100,255};
                }
                if(IsMouseButtonReleased(0) || (IsGamepadButtonReleased(0,GAMEPAD_BUTTON_RIGHT_FACE_DOWN) && controllerStates == ControllerMainMenuStates::QuitButton)){
                    CloseWindow();
                }
            }else{
                quitColor = {255,255,255,255};
            }

            break;


        case MenuScreenStates::LoadGameScreen:

            if(CheckCollisionPointRec(vMousePosition, deleteSave1ButtonRec)|| controllerStates == ControllerMainMenuStates::DeleteGame1){
                deleteSave1ButtonIndex = 1;
                if(IsMouseButtonDown(0) || (IsGamepadButtonPressed(0,GAMEPAD_BUTTON_RIGHT_FACE_DOWN) && controllerStates == ControllerMainMenuStates::DeleteGame1)){
                    deleteSave1ButtonIndex = 2;
                }
                if(IsMouseButtonReleased(0) || (IsGamepadButtonReleased(0,GAMEPAD_BUTTON_RIGHT_FACE_DOWN) && controllerStates == ControllerMainMenuStates::DeleteGame1)){
                    // delete save 1
                }
            }else{
                deleteSave1ButtonIndex = 0;
            }

            if(CheckCollisionPointRec(vMousePosition, deleteSave2ButtonRec)|| controllerStates == ControllerMainMenuStates::DeleteGame2){
                deleteSave2ButtonIndex = 1;
                if(IsMouseButtonDown(0) || (IsGamepadButtonPressed(0,GAMEPAD_BUTTON_RIGHT_FACE_DOWN) && controllerStates == ControllerMainMenuStates::DeleteGame2)){
                    deleteSave2ButtonIndex = 2;
                }
                if(IsMouseButtonReleased(0) || (IsGamepadButtonReleased(0,GAMEPAD_BUTTON_RIGHT_FACE_DOWN) && controllerStates == ControllerMainMenuStates::DeleteGame2)){
                    // delete save 2
                }
            }else{
                deleteSave2ButtonIndex = 0;
            }

            if(CheckCollisionPointRec(vMousePosition, deleteSave3ButtonRec)|| controllerStates == ControllerMainMenuStates::DeleteGame3){
                deleteSave3ButtonIndex = 1;
                if(IsMouseButtonDown(0) || (IsGamepadButtonPressed(0,GAMEPAD_BUTTON_RIGHT_FACE_DOWN) && controllerStates == ControllerMainMenuStates::DeleteGame3)){
                    deleteSave3ButtonIndex = 2;
                }
                if(IsMouseButtonReleased(0) || (IsGamepadButtonReleased(0,GAMEPAD_BUTTON_RIGHT_FACE_DOWN) && controllerStates == ControllerMainMenuStates::DeleteGame3)){
                    // delete save 3
                }
            }else{
                deleteSave3ButtonIndex = 0;
            }

            if(CheckCollisionPointRec(vMousePosition, loadSave1ButtonRec)|| (controllerStates == ControllerMainMenuStates::LoadGame1 && controllerActive)){
                loadSave1Color = {200,200,200,255};
                if(IsMouseButtonDown(0) || (IsGamepadButtonPressed(0,GAMEPAD_BUTTON_RIGHT_FACE_DOWN) && controllerStates == ControllerMainMenuStates::LoadGame1)){
                    loadSave1Color = {100,100,100,255};
                }
                if(IsMouseButtonReleased(0) || (IsGamepadButtonReleased(0,GAMEPAD_BUTTON_RIGHT_FACE_DOWN) && controllerStates == ControllerMainMenuStates::LoadGame1)){
                    sceneManager->SetNextScene(std::make_unique<Tutorial>(sceneName));
                }
            }else{
                loadSave1Color = {255,255,255,255};
            }

            if(CheckCollisionPointRec(vMousePosition, loadSave2ButtonRec) || controllerStates == ControllerMainMenuStates::LoadGame2){
                loadSave2Color = {200,200,200,255};
                if(IsMouseButtonDown(0) || (IsGamepadButtonPressed(0,GAMEPAD_BUTTON_RIGHT_FACE_DOWN)&& controllerStates == ControllerMainMenuStates::LoadGame2)){
                    loadSave2Color = {100,100,100,255};
                }
                if(IsMouseButtonReleased(0) || (IsGamepadButtonReleased(0,GAMEPAD_BUTTON_RIGHT_FACE_DOWN)&& controllerStates == ControllerMainMenuStates::LoadGame2)){
                    sceneManager->SetNextScene(std::make_unique<Tutorial>(sceneName));
                }
            }else{
                loadSave2Color = {255,255,255,255};
            }

            if(CheckCollisionPointRec(vMousePosition, loadSave3ButtonRec) || controllerStates == ControllerMainMenuStates::LoadGame3){
                loadSave3Color = {200,200,200,255};
                if(IsMouseButtonDown(0) || (IsGamepadButtonPressed(0,GAMEPAD_BUTTON_RIGHT_FACE_DOWN) && controllerStates == ControllerMainMenuStates::LoadGame3)){
                    loadSave3Color = {100,100,100,255};
                }
                if(IsMouseButtonReleased(0) || (IsGamepadButtonReleased(0,GAMEPAD_BUTTON_RIGHT_FACE_DOWN) && controllerStates == ControllerMainMenuStates::LoadGame3)){
                    sceneManager->SetNextScene(std::make_unique<Tutorial>(sceneName));
                }
            }else{
                loadSave3Color = {255,255,255,255};
            }

            if(CheckCollisionPointRec(vMousePosition, backButtonRec)){
                backButtonColor = {200,200,200,255};
                if(IsMouseButtonDown(0)){
                    backButtonColor = {100,100,100,255};
                }
                if(IsMouseButtonReleased(0)){
                    controllerStates = ControllerMainMenuStates::PlayGameButton;
                    menuScreenStates = MenuScreenStates::TitleScreen;
                }
            }else{
                backButtonColor = {255,255,255,255};
            }
            if(IsGamepadButtonReleased(0,GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)){
                controllerStates = ControllerMainMenuStates::PlayGameButton;
                menuScreenStates = MenuScreenStates::TitleScreen;
            }
            break;
        case MenuScreenStates::SettingsScreen:

            for(int i=0;i<10;i++) { // Changing Sound and Music Volume
                if (CheckCollisionPointRec(vMousePosition, musicVolumeRecs[i])) {
                    if(IsMouseButtonReleased(0)) {
                        musicVolume = i;
                        UpdateMusicAndSoundVolume();
                        break;
                    }
                }
                if (CheckCollisionPointRec(vMousePosition, soundVolumeRecs[i])) {
                    if(IsMouseButtonReleased(0)) {
                        soundVolume = i;
                        UpdateMusicAndSoundVolume();
                        break;
                    }
                }

            }


            if(CheckCollisionPointRec(vMousePosition,fullscreenRec) || controllerStates == ControllerMainMenuStates::ChangeFullscreen){
                if(IsMouseButtonReleased(0) || (IsGamepadButtonReleased(0,GAMEPAD_BUTTON_RIGHT_FACE_DOWN) && controllerStates == ControllerMainMenuStates::ChangeFullscreen)){
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
                backButtonColor = {200,200,200,255};
                if(IsMouseButtonDown(0)){
                    backButtonColor = {100,100,100,255};
                }
                if(IsMouseButtonReleased(0)){
                    controllerStates = ControllerMainMenuStates::PlayGameButton;
                    menuScreenStates = MenuScreenStates::TitleScreen;
                }
            }else{
                backButtonColor = {255,255,255,255};
            }

            if(IsGamepadButtonReleased(0,GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)){
                controllerStates = ControllerMainMenuStates::PlayGameButton;
                menuScreenStates = MenuScreenStates::TitleScreen;
            }

            break;
        case MenuScreenStates::CreditsScreen:

            if(CheckCollisionPointRec(vMousePosition, backButtonRec)){
                backButtonColor = {200,200,200,255};
                if(IsMouseButtonDown(0)){
                    backButtonColor = {100,100,100,255};
                }
                if(IsMouseButtonReleased(0)){
                    controllerStates = ControllerMainMenuStates::PlayGameButton;
                    menuScreenStates = MenuScreenStates::TitleScreen;
                }
            }else{
                backButtonColor = {255,255,255,255};
            }

            if(IsGamepadButtonReleased(0,GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)){
                controllerStates = ControllerMainMenuStates::PlayGameButton;
                menuScreenStates = MenuScreenStates::TitleScreen;
            }

            break;
    }

    if(IsGamepadButtonDown(0,GAMEPAD_BUTTON_RIGHT_FACE_RIGHT) && !controllerActive){ // Activate Controller by pressing A
        controllerActive = true;
    }

    if(controllerActive){ // Navigating with Controller in Main Menu
        if(IsGamepadButtonPressed(0,GAMEPAD_BUTTON_LEFT_FACE_UP)){
            UpdateByController(ControllerCommands::MOVEUP);
        }
        if(IsGamepadButtonPressed(0,GAMEPAD_BUTTON_LEFT_FACE_RIGHT)){
            UpdateByController(ControllerCommands::MOVERIGHT);
        }
        if(IsGamepadButtonPressed(0,GAMEPAD_BUTTON_LEFT_FACE_DOWN)){
            UpdateByController(ControllerCommands::MOVEDOWN);
        }
        if(IsGamepadButtonPressed(0,GAMEPAD_BUTTON_LEFT_FACE_LEFT)){
            UpdateByController(ControllerCommands::MOVELEFT);
        }
    }

  
}

void MainMenu::Draw() {
    switch (menuScreenStates) {
        case MenuScreenStates::TitleScreen:
            DrawTexture(mainMenuBackground,0,0,WHITE);
            DrawTexture(gameTitlePicture,450,60,WHITE);
            DrawTexture(playButton,(float)playButtonRec.x,(float)playButtonRec.y,playButtonColor);
            DrawTexture(settingsButton,(float)settingsButtonRec.x,(float)settingsButtonRec.y,settingsColor);
            DrawTexture(creditsButton,(float)creditsButtonRec.x,(float)creditsButtonRec.y,creditsColor);
            DrawTexture(quitButton,(float)quitButtonRec.x,(float)quitButtonRec.y,quitColor);

            break;

        case MenuScreenStates::LoadGameScreen:

            DrawTexture(loadSave1Button,loadSave1ButtonRec.x,loadSave1ButtonRec.y,loadSave1Color);
            DrawTexture(loadSave2Button,loadSave2ButtonRec.x,loadSave2ButtonRec.y,loadSave2Color);
            DrawTexture(loadSave3Button,loadSave3ButtonRec.x,loadSave3ButtonRec.y,loadSave3Color);

            DrawTexture(savegameTex1,75,150,WHITE);
            DrawTexture(savegameTex2,485,150,WHITE);
            DrawTexture(savegameTex3,895,150,WHITE);

            DrawTexture(deleteSave1Button[deleteSave1ButtonIndex],deleteSave1ButtonRec.x,deleteSave1ButtonRec.y,WHITE);
            DrawTexture(deleteSave2Button[deleteSave2ButtonIndex],deleteSave2ButtonRec.x,deleteSave2ButtonRec.y,WHITE);
            DrawTexture(deleteSave3Button[deleteSave3ButtonIndex],deleteSave3ButtonRec.x,deleteSave3ButtonRec.y,WHITE);

            DrawTexture(backButton, (float)backButtonRec.x, (float)backButtonRec.y, backButtonColor);
            break;

        case MenuScreenStates::SettingsScreen:

            if(controllerActive && controllerStates==ControllerMainMenuStates::ChangeMusic){DrawRectangle(26,56,355,110,ORANGE);}
            DrawTexture(musicText,30,60,WHITE);
            if(controllerActive && controllerStates==ControllerMainMenuStates::ChangeSound){DrawRectangle(26,196,355,110,ORANGE);}
            DrawTexture(soundText,30,200,WHITE);
            if(controllerActive && controllerStates==ControllerMainMenuStates::ChangeFullscreen){DrawRectangle(26,336,355,110,ORANGE);}
            DrawTexture(displayText,30,340,WHITE);

            for(int i = 0; i<10;i++){ // Drawing Sound and Music Recs in Settings
                if(isMusicVolumeRecActive[i]){
                    if(musicVolume == 0 && i == 0){
                        DrawTexture(redHearth,musicVolumeRecs[i].x,musicVolumeRecs[i].y,WHITE);
                    }
                    else DrawTexture(orangeHearth,musicVolumeRecs[i].x,musicVolumeRecs[i].y,WHITE);
                }else DrawTexture(emptyHearth,musicVolumeRecs[i].x,musicVolumeRecs[i].y,WHITE);
                if(isSoundVolumeRecActive[i]){
                    if(soundVolume == 0 && i == 0){
                        DrawTexture(redHearth,soundVolumeRecs[i].x,soundVolumeRecs[i].y,WHITE);
                    } else DrawTexture(orangeHearth,soundVolumeRecs[i].x,soundVolumeRecs[i].y,WHITE);
                }else DrawTexture(emptyHearth,soundVolumeRecs[i].x,soundVolumeRecs[i].y,WHITE);
            }

            if(isFullScreenActive){ // Fullscreen Rec
                DrawTexture(redHearth,fullscreenRec.x,fullscreenRec.y,WHITE);
            }else DrawTexture(emptyHearth,fullscreenRec.x,fullscreenRec.y,WHITE);

            DrawTexture(backButton, (float)backButtonRec.x, (float)backButtonRec.y, backButtonColor);

            break;

        case MenuScreenStates::CreditsScreen: // Drawings Credits

            DrawText("Adrian Pfaff - Lead Programmer - Workflows \nAmar Civic - Programmer - Marketing \nRobin Günther - Programmer - UML-Diagrams \nPascal Hirt - Programmer - Sound and Music \nAykan Akgül - Lead Designer - World Design \nAndrea Preussner - Lead Artist - Animation",200,140,40,WHITE); // I am sorry
            DrawTexture(backButton, (float)backButtonRec.x, (float)backButtonRec.y, backButtonColor);

            break;
    }
    if(!controllerActive) {
        DrawText("Press Gamepad B to activate Gamepad in Main Menu.",720,680,20,WHITE);
    }else DrawText("Press Gamepad A to select and Gamepad B to Return.",700,680,20,WHITE);
}

MainMenu::~MainMenu()
{
    
}

int MainMenu::GetMusicVolume() {
    return musicVolume;
}

int MainMenu::GetSoundVolume() {
    return soundVolume;
}

void MainMenu::SetMusicVolume(int volume) {
    musicVolume = volume;
    for(int e = 0; e < 10; e++){
        if(e <= musicVolume){
            isMusicVolumeRecActive[e] = true;
        }else isMusicVolumeRecActive[e] = false;
    }
}

void MainMenu::SetSoundVolume(int volume) {
    soundVolume = volume;
    for(int e = 0; e < 10; e++){
        if(e <= soundVolume){
            isSoundVolumeRecActive[e] = true;
        }else isSoundVolumeRecActive[e] = false;
    }
}

bool MainMenu::GetFullscreenActive() {
    return isFullScreenActive;
}

void MainMenu::SetFullscreenActive(bool active) {
    isFullScreenActive = active;
    if(isFullScreenActive && !IsWindowFullscreen()){
        ToggleFullscreen();
    }
    if(!isFullScreenActive && IsWindowFullscreen()){
        ToggleFullscreen();
    }
}

void MainMenu::UpdateByController(ControllerCommands controllerCommmand) {
    switch(controllerCommmand){
        case ControllerCommands::MOVEUP:
            switch(controllerStates){
                case ControllerMainMenuStates::SettingsButton: controllerStates = ControllerMainMenuStates::PlayGameButton;
                    break;
                case ControllerMainMenuStates::CreditsButton: controllerStates = ControllerMainMenuStates::SettingsButton;
                    break;
                case ControllerMainMenuStates::QuitButton: controllerStates = ControllerMainMenuStates::CreditsButton;
                    break;
                case ControllerMainMenuStates::LoadGame1: controllerStates = ControllerMainMenuStates::DeleteGame1;
                    break;
                case ControllerMainMenuStates::LoadGame2: controllerStates = ControllerMainMenuStates::DeleteGame2;
                    break;
                case ControllerMainMenuStates::LoadGame3: controllerStates = ControllerMainMenuStates::DeleteGame3;
                    break;
                case ControllerMainMenuStates::ChangeSound: controllerStates = ControllerMainMenuStates::ChangeMusic;
                    break;
                case ControllerMainMenuStates::ChangeFullscreen: controllerStates = ControllerMainMenuStates::ChangeSound;
                    break;
            }
            break;
        case ControllerCommands::MOVERIGHT:
            switch(controllerStates) {
                case ControllerMainMenuStates::LoadGame1: controllerStates = ControllerMainMenuStates::LoadGame2;
                    break;
                case ControllerMainMenuStates::LoadGame2: controllerStates = ControllerMainMenuStates::LoadGame3;
                    break;
                case ControllerMainMenuStates::DeleteGame1: controllerStates = ControllerMainMenuStates::DeleteGame2;
                    break;
                case ControllerMainMenuStates::DeleteGame2: controllerStates = ControllerMainMenuStates::DeleteGame3;
                    break;
                case ControllerMainMenuStates::ChangeMusic:
                    if(musicVolume<9){
                        ++musicVolume;
                        UpdateMusicAndSoundVolume();
                    }
                    break;
                case ControllerMainMenuStates::ChangeSound:
                    if(soundVolume<9){
                        ++soundVolume;
                        UpdateMusicAndSoundVolume();
                    }
                    break;
            }
            break;
        case ControllerCommands::MOVEDOWN:
            switch(controllerStates){
                case ControllerMainMenuStates::PlayGameButton: controllerStates = ControllerMainMenuStates::SettingsButton;
                    break;
                case ControllerMainMenuStates::SettingsButton: controllerStates = ControllerMainMenuStates::CreditsButton;
                    break;
                case ControllerMainMenuStates::CreditsButton: controllerStates = ControllerMainMenuStates::QuitButton;
                    break;
                case ControllerMainMenuStates::DeleteGame1: controllerStates = ControllerMainMenuStates::LoadGame1;
                    break;
                case ControllerMainMenuStates::DeleteGame2: controllerStates = ControllerMainMenuStates::LoadGame2;
                    break;
                case ControllerMainMenuStates::DeleteGame3: controllerStates = ControllerMainMenuStates::LoadGame3;
                    break;
                case ControllerMainMenuStates::ChangeMusic: controllerStates = ControllerMainMenuStates::ChangeSound;
                    break;
                case ControllerMainMenuStates::ChangeSound: controllerStates = ControllerMainMenuStates::ChangeFullscreen;
                    break;
            }
            break;
        case ControllerCommands::MOVELEFT:
            switch(controllerStates) {
                case ControllerMainMenuStates::LoadGame2: controllerStates = ControllerMainMenuStates::LoadGame1;
                    break;
                case ControllerMainMenuStates::LoadGame3: controllerStates = ControllerMainMenuStates::LoadGame2;
                    break;
                case ControllerMainMenuStates::DeleteGame2: controllerStates = ControllerMainMenuStates::DeleteGame1;
                    break;
                case ControllerMainMenuStates::DeleteGame3: controllerStates = ControllerMainMenuStates::DeleteGame2;
                    break;
                case ControllerMainMenuStates::ChangeMusic:
                    if(musicVolume>0){
                        --musicVolume;
                        UpdateMusicAndSoundVolume();
                    }
                    break;
                case ControllerMainMenuStates::ChangeSound:
                    if(soundVolume>0){
                        --soundVolume;
                        UpdateMusicAndSoundVolume();
                    }
                    break;
            }
            break;
    }
}

void MainMenu::UpdateMusicAndSoundVolume() {
    for(int i = 0; i<10;i++){ // Activating the Sound and Music Rectangles TODO(temp only rework after save and load is finished)
        musicVolumeRecs[i] = {(float)(600+(60*i)),60,50,50};
        if(musicVolume>=i){
            isMusicVolumeRecActive[i] = true;
        }else isMusicVolumeRecActive[i] = false;
        if(soundVolume>=i){
            isSoundVolumeRecActive[i] = true;
        }else isSoundVolumeRecActive[i] = false;
        soundVolumeRecs[i] = {(float)(600+(60*i)),200,50,50};
    }

    soundManager->SetSfxVolume(0.2*soundVolume);
    soundManager->SetTrackVolume(0.2*musicVolume);
}
