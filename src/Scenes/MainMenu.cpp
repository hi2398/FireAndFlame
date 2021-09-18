#include "MainMenu.h"
#include "../Global.h"
#include <iostream>
#include <filesystem>
#include "Tutorial.h"

MainMenu::MainMenu(SceneEnums lastScene) : Scene(SceneEnums::Default) {
    this->lastScene = lastScene;
    tilemap=std::make_unique<Tilemap>();
    playerCharacter->active = false; // Disables Player

    introRaylib = LoadTexture("assets/graphics/GUI/MadeWithRaylib.png");
    introIgnite = LoadTexture("assets/graphics/GUI/TeamIgnite.png");

    mainMenuBackground = LoadTexture("assets/graphics/GUI/fireAndFlame.png");
    secondaryBackground = LoadTexture("assets/graphics/GUI/secondaryBackground.png");
    gameTitlePicture = LoadTexture("assets/graphics/GUI/fireAndFlameLogo.png");// The Title of our Game as a PNG Image, instead of Font only

    // Button Rectangle and Textures from Start Button in Title Screen
    playButton[0] = LoadTexture("assets/graphics/GUI/loadGame.png");
    playButton[1] = LoadTexture("assets/graphics/GUI/LoadGlow.png");
    playButtonRec = {30,60,(float)playButton[0].width,(float)playButton[0].height};

    // Button Rectangle and Textures from Settings Button in Title Screen
    settingsButton[0] = LoadTexture("assets/graphics/GUI/settingsButton.png");
    settingsButton[1] = LoadTexture("assets/graphics/GUI/SettingsGlow.png");
    settingsButtonRec = {30,200,(float)settingsButton[0].width,(float)settingsButton[0].height};

    // Button Rectangle and Textures from Credits Button in Title Screen
    creditsButton[0] = LoadTexture("assets/graphics/GUI/creditsButton.png");
    creditsButton[1] = LoadTexture("assets/graphics/GUI/CreditsGlow.png");
    creditsButtonRec = {30,340,(float)creditsButton[0].width,(float)creditsButton[0].height};

    // Button Rectangle and Textures from Quit Button in Title Screen
    quitButton[0] = LoadTexture("assets/graphics/GUI/quitButton.png");
    quitButton[1] = LoadTexture("assets/graphics/GUI/QuitGlow.png");
    quitButtonRec = {30,480,(float)quitButton[0].width,(float)quitButton[0].height};


    // Buttons for Save and Load
    std::string saveFolder="./Saves/";
    std::string saveScreen=saveFolder + "save" + "_" + "1" + ".png";
    savegameTex1 = LoadTexture(saveScreen.c_str());
    saveScreen=saveFolder + "save" + "_" + "2" + ".png";
    savegameTex2 = LoadTexture(saveScreen.c_str());
    saveScreen=saveFolder + "save" + "_" + "3" + ".png";
    savegameTex3 = LoadTexture(saveScreen.c_str());

    loadSave1Button[0] = LoadTexture("assets/graphics/GUI/loadsave.png");
    loadSave1Button[1] = LoadTexture("assets/graphics/GUI/loadGlowMini.png");
    loadSave1ButtonRec = {50,480,(float)loadSave1Button[0].width,(float)loadSave1Button[0].height};

    loadSave2Button[0] = LoadTexture("assets/graphics/GUI/loadsave.png");
    loadSave2Button[1] = LoadTexture("assets/graphics/GUI/loadGlowMini.png");
    loadSave2ButtonRec = {460,480,(float)loadSave2Button[0].width,(float)loadSave2Button[0].height};

    loadSave3Button[0] = LoadTexture("assets/graphics/GUI/loadsave.png");
    loadSave3Button[1] = LoadTexture("assets/graphics/GUI/loadGlowMini.png");
    loadSave3ButtonRec = {870,480,(float)loadSave3Button[0].width,(float)loadSave3Button[0].height};

    deleteSave1Button[0] = LoadTexture("assets/graphics/GUI/resetButton.png");
    deleteSave1Button[1] = LoadTexture("assets/graphics/GUI/ResetSaveGlow.png");
    deleteSave1ButtonRec = {76.5,40,275,75};

    deleteSave2Button[0] = LoadTexture("assets/graphics/GUI/resetButton.png");
    deleteSave2Button[1] = LoadTexture("assets/graphics/GUI/ResetSaveGlow.png");
    deleteSave2ButtonRec = {485,40,275,75};

    deleteSave3Button[0] = LoadTexture("assets/graphics/GUI/resetButton.png");
    deleteSave3Button[1] = LoadTexture("assets/graphics/GUI/ResetSaveGlow.png");
    deleteSave3ButtonRec = {894.5,40,275,75};


    // Button Rectangle and Textures from Back Button in Settings and Credits Screen
    backButton[0] = LoadTexture("assets/graphics/GUI/backButton.png");
    backButton[1] = LoadTexture("assets/graphics/GUI/backGlow.png");

    backButtonRec = {30, 590, (float)backButton[0].width, (float)backButton[0].height};

    emptyHearth = LoadTexture("assets/graphics/GUI/emptyHearth.png");
    orangeHearth = LoadTexture("assets/graphics/GUI/orangeHearth.png");
    redHearth = LoadTexture("assets/graphics/GUI/redHearth.png");

    musicText = LoadTexture("assets/graphics/GUI/musicText.png");
    soundText = LoadTexture("assets/graphics/GUI/soundText.png");
    displayText = LoadTexture("assets/graphics/GUI/displayText.png");

    for(int i = 0; i<10;i++){ // Activating the Sound and Music Rectangles TODO(temp only rework after save and load is finished)
        musicVolumeRecs[i] = {(float)(400+(60*i)),60,50,50};
        soundVolumeRecs[i] = {(float)(400+(60*i)),200,50,50};
    }
    UpdateMusicAndSoundVolume();
    fullscreenRec = {460,360,50,50};

    //load soundtrack
    track = LoadMusicStream("assets/audio/tracks/title_screen.mp3");
    PlayMusicStream(track);
}

void MainMenu::Update() {
    SetMusicVolume(track, soundManager->GetTrackVolume());
    Scene::Update();
    if (IsGamepadAvailable(0)) { // Activates Controller
        controllerActive = true;
    }
    else { controllerActive = false; }
    if(isIntroDone) {
        UpdateMusicStream(track);
        vMousePosition = sceneManager->GetVirtualMousePosition(); // Gets the virtual mouse position

        if(introFade.a != 0){
            introFade.a -=3;
        }

        switch (menuScreenStates) {

            case MenuScreenStates::TitleScreen:

                if (CheckCollisionPointRec(vMousePosition, playButtonRec) ||
                    (controllerStates == ControllerMainMenuStates::PlayGameButton &&
                     controllerActive)) { // Handles the Button State of Play
                    playButtonIndex = 1;
                    if (IsMouseButtonDown(0) ||
                        (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) && controllerActive) &&
                        controllerStates == ControllerMainMenuStates::PlayGameButton) {
                        playButtonColor = {100, 100, 100, 255};
                    }
                    if (IsMouseButtonReleased(0) ||
                        (IsGamepadButtonReleased(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) && controllerActive) &&
                        controllerStates == ControllerMainMenuStates::PlayGameButton) {
                        controllerStates = ControllerMainMenuStates::LoadGame1;
                        menuScreenStates = MenuScreenStates::LoadGameScreen;
                    }
                } else {
                    playButtonIndex = 0;
                    playButtonColor = {255, 255, 255, 255};
                }


                if (CheckCollisionPointRec(vMousePosition, settingsButtonRec) || controllerStates ==
                                                                                 ControllerMainMenuStates::SettingsButton) { // Handles the Button State of Settings
                    settingsIndex = 1;
                    if (IsMouseButtonDown(0) || (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) &&
                                                 controllerStates == ControllerMainMenuStates::SettingsButton)) {
                        settingsColor = {100, 100, 100, 255};
                    }
                    if (IsMouseButtonReleased(0) || (IsGamepadButtonReleased(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) &&
                                                     controllerStates == ControllerMainMenuStates::SettingsButton)) {
                        controllerStates = ControllerMainMenuStates::ChangeMusic;
                        menuScreenStates = MenuScreenStates::SettingsScreen;
                    }
                } else {
                    settingsIndex = 0;
                    settingsColor = {255, 255, 255, 255};
                }


                if (CheckCollisionPointRec(vMousePosition, creditsButtonRec) || controllerStates ==
                                                                                ControllerMainMenuStates::CreditsButton) { // Handles the Button State of Credits
                    creditsIndex = 1;
                    if (IsMouseButtonDown(0) || (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) &&
                                                 controllerStates == ControllerMainMenuStates::CreditsButton)) {
                        creditsColor = {100, 100, 100, 255};
                    }
                    if (IsMouseButtonReleased(0) || (IsGamepadButtonReleased(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) &&
                                                     controllerStates == ControllerMainMenuStates::CreditsButton)) {
                        menuScreenStates = MenuScreenStates::CreditsScreen;
                    }
                } else {
                    creditsIndex = 0;
                    creditsColor = {255, 255, 255, 255};
                }


                if (CheckCollisionPointRec(vMousePosition, quitButtonRec) ||
                    controllerStates == ControllerMainMenuStates::QuitButton) { // Handles the Button State of Quit
                    quitIndex = 1;
                    if (IsMouseButtonDown(0) || (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) &&
                                                 controllerStates == ControllerMainMenuStates::QuitButton)) {
                        quitColor = {100, 100, 100, 255};
                    }
                    if (IsMouseButtonReleased(0) || (IsGamepadButtonReleased(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) &&
                                                     controllerStates == ControllerMainMenuStates::QuitButton)) {
                        CloseWindow();
                    }
                } else {
                    quitIndex = 0;
                    quitColor = {255, 255, 255, 255};
                }

                break;


            case MenuScreenStates::LoadGameScreen:

                if (CheckCollisionPointRec(vMousePosition, deleteSave1ButtonRec) ||
                    controllerStates == ControllerMainMenuStates::DeleteGame1) {
                    deleteSave1Index = 1;
                    if ((IsMouseButtonDown(0) && CheckCollisionPointRec(vMousePosition, deleteSave1ButtonRec))|| (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) &&
                                                 controllerStates == ControllerMainMenuStates::DeleteGame1)) {
                        deleteSave1Color = {100, 100, 100, 255};
                    }
                    if ((IsMouseButtonReleased(0) && CheckCollisionPointRec(vMousePosition, deleteSave1ButtonRec)) || (IsGamepadButtonReleased(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) &&
                                                     controllerStates == ControllerMainMenuStates::DeleteGame1)) {
                        // delete save 1
                        ResetSave(1);
                    }
                } else {
                    deleteSave1Index = 0;
                    deleteSave1Color = {255, 255, 255, 255};
                }

                if (CheckCollisionPointRec(vMousePosition, deleteSave2ButtonRec) ||
                    controllerStates == ControllerMainMenuStates::DeleteGame2) {
                    deleteSave2Index = 1;
                    if ((IsMouseButtonDown(0) && CheckCollisionPointRec(vMousePosition, deleteSave2ButtonRec))|| (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) &&
                                                 controllerStates == ControllerMainMenuStates::DeleteGame2)) {
                        deleteSave2Color = {100, 100, 100, 255};
                    }
                    if ((IsMouseButtonDown(0) && CheckCollisionPointRec(vMousePosition, deleteSave2ButtonRec)) || (IsGamepadButtonReleased(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) &&
                                                     controllerStates == ControllerMainMenuStates::DeleteGame2)) {
                        // delete save 2
                        ResetSave(2);
                    }
                } else {
                    deleteSave2Index = 0;
                    deleteSave2Color = {255, 255, 255, 255};
                }

                if (CheckCollisionPointRec(vMousePosition, deleteSave3ButtonRec) ||
                    controllerStates == ControllerMainMenuStates::DeleteGame3) {
                    deleteSave3Index = 1;
                    if ((IsMouseButtonDown(0) && CheckCollisionPointRec(vMousePosition, deleteSave3ButtonRec)) || (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) &&
                                                 controllerStates == ControllerMainMenuStates::DeleteGame3)) {
                        deleteSave3Color = {100, 100, 100, 255};
                    }
                    if ((IsMouseButtonDown(0) && CheckCollisionPointRec(vMousePosition, deleteSave3ButtonRec)) || (IsGamepadButtonReleased(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) &&
                                                     controllerStates == ControllerMainMenuStates::DeleteGame3)) {
                        // delete save 3
                        ResetSave(3);
                    }
                } else {
                    deleteSave3Index = 0;
                    deleteSave3Color = {255, 255, 255, 255};
                }

                if (CheckCollisionPointRec(vMousePosition, loadSave1ButtonRec) ||
                    (controllerStates == ControllerMainMenuStates::LoadGame1 && controllerActive)) {
                    loadSave1Index = 1;
                    if ((IsMouseButtonDown(0) && CheckCollisionPointRec(vMousePosition, loadSave1ButtonRec)) || (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) &&
                                                 controllerStates == ControllerMainMenuStates::LoadGame1)) {
                        loadSave1Color = {100, 100, 100, 255};
                    }
                    if ((IsMouseButtonDown(0) && CheckCollisionPointRec(vMousePosition, loadSave1ButtonRec)) || (IsGamepadButtonReleased(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) &&
                                                     controllerStates == ControllerMainMenuStates::LoadGame1)) {
                        sceneManager->SetActiveSaveSlot(1);
                        sceneManager->LoadGame("./Saves/", 1);
                    }
                } else {
                    loadSave1Index = 0;
                    loadSave1Color = {255, 255, 255, 255};
                }

                if (CheckCollisionPointRec(vMousePosition, loadSave2ButtonRec) ||
                    controllerStates == ControllerMainMenuStates::LoadGame2) {
                    loadSave2Index = 1;
                    if ((IsMouseButtonDown(0) && CheckCollisionPointRec(vMousePosition, loadSave2ButtonRec)) || (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) &&
                                                 controllerStates == ControllerMainMenuStates::LoadGame2)) {
                        loadSave2Color = {100, 100, 100, 255};
                    }
                    if ((IsMouseButtonDown(0) && CheckCollisionPointRec(vMousePosition, loadSave2ButtonRec)) || (IsGamepadButtonReleased(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) &&
                                                     controllerStates == ControllerMainMenuStates::LoadGame2)) {
                        sceneManager->SetActiveSaveSlot(2);
                        sceneManager->LoadGame("./Saves/", 2);
                    }
                } else {
                    loadSave2Index = 0;
                    loadSave2Color = {255, 255, 255, 255};
                }

                if (CheckCollisionPointRec(vMousePosition, loadSave3ButtonRec) ||
                    controllerStates == ControllerMainMenuStates::LoadGame3) {
                    loadSave3Index = 1;
                    if ((IsMouseButtonDown(0) && CheckCollisionPointRec(vMousePosition, loadSave3ButtonRec))|| (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) &&
                                                 controllerStates == ControllerMainMenuStates::LoadGame3)) {
                        loadSave3Color = {100, 100, 100, 255};
                    }
                    if ((IsMouseButtonDown(0) && CheckCollisionPointRec(vMousePosition, loadSave3ButtonRec)) || (IsGamepadButtonReleased(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) &&
                                                     controllerStates == ControllerMainMenuStates::LoadGame3)) {
                        sceneManager->SetActiveSaveSlot(3);
                        sceneManager->LoadGame("./Saves/", 3);
                    }
                } else {
                    loadSave3Index = 0;
                    loadSave3Color = {255, 255, 255, 255};
                }

                if (CheckCollisionPointRec(vMousePosition, backButtonRec)) {
                    backButtonIndex = 1;
                    if (IsMouseButtonDown(0)) {
                        backButtonColor = {100, 100, 100, 255};
                    }
                    if (IsMouseButtonReleased(0)) {
                        playButtonColor = { 255, 255, 255, 255 };
                        quitColor = { 255, 255, 255, 255 };
                        creditsColor = { 255, 255, 255, 255 };
                        settingsColor = { 255, 255, 255, 255 };
                        controllerStates = ControllerMainMenuStates::PlayGameButton;
                        menuScreenStates = MenuScreenStates::TitleScreen;
                    }
                } else {
                    backButtonColor = {255, 255, 255, 255};
                    backButtonIndex = 0;
                }
                if (IsGamepadButtonReleased(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) {
                    playButtonColor = { 255, 255, 255, 255 };
                    quitColor = { 255, 255, 255, 255 };
                    creditsColor = { 255, 255, 255, 255 };
                    settingsColor = { 255, 255, 255, 255 };
                    controllerStates = ControllerMainMenuStates::PlayGameButton;
                    menuScreenStates = MenuScreenStates::TitleScreen;
                }
                break;
            case MenuScreenStates::SettingsScreen:

                for (int i = 0; i < 10; i++) { // Changing Sound and Music Volume
                    if (CheckCollisionPointRec(vMousePosition, musicVolumeRecs[i])) {
                        if (IsMouseButtonReleased(0)) {
                            musicVolume = i;
                            UpdateMusicAndSoundVolume();
                            break;
                        }
                    }
                    if (CheckCollisionPointRec(vMousePosition, soundVolumeRecs[i])) {
                        if (IsMouseButtonReleased(0)) {
                            soundVolume = i;
                            UpdateMusicAndSoundVolume();
                            soundManager->PlaySfx(SFX::TEST);
                            break;
                        }
                    }

                }


                if (CheckCollisionPointRec(vMousePosition, fullscreenRec) ||
                    controllerStates == ControllerMainMenuStates::ChangeFullscreen) {
                    if (IsMouseButtonReleased(0) || (IsGamepadButtonReleased(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) &&
                                                     controllerStates == ControllerMainMenuStates::ChangeFullscreen)) {
                        isFullScreenActive = !isFullScreenActive;
                        if (isFullScreenActive && !IsWindowFullscreen()) {
                            ToggleFullscreen();
                        }
                        if (!isFullScreenActive && IsWindowFullscreen()) {
                            ToggleFullscreen();
                        }
                    }
                }


                if (CheckCollisionPointRec(vMousePosition, backButtonRec)) {
                    backButtonIndex = 1;
                    if (IsMouseButtonDown(0)) {
                        backButtonColor = {100, 100, 100, 255};
                    }
                    if (IsMouseButtonReleased(0)) {
                        playButtonColor = { 255, 255, 255, 255 };
                        quitColor = { 255, 255, 255, 255 };
                        creditsColor = { 255, 255, 255, 255 };
                        settingsColor = { 255, 255, 255, 255 };
                        controllerStates = ControllerMainMenuStates::PlayGameButton;
                        menuScreenStates = MenuScreenStates::TitleScreen;
                    }
                } else {
                    backButtonIndex = 0;
                    backButtonColor = {255, 255, 255, 255};
                }

                if (IsGamepadButtonReleased(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) {
                    playButtonColor = { 255, 255, 255, 255 };
                    quitColor = { 255, 255, 255, 255 };
                    creditsColor = { 255, 255, 255, 255 };
                    settingsColor = { 255, 255, 255, 255 };
                    controllerStates = ControllerMainMenuStates::PlayGameButton;
                    menuScreenStates = MenuScreenStates::TitleScreen;
                }

                break;
            case MenuScreenStates::CreditsScreen:

                if (CheckCollisionPointRec(vMousePosition, backButtonRec)) {
                    backButtonIndex = 1;
                    if (IsMouseButtonDown(0)) {
                        backButtonColor = {100, 100, 100, 255};
                    }
                    if (IsMouseButtonReleased(0)) {
                        quitColor = { 255, 255, 255, 255 };
                        creditsColor = { 255, 255, 255, 255 };
                        settingsColor = { 255, 255, 255, 255 };
                        playButtonColor = { 255, 255, 255, 255 };
                        controllerStates = ControllerMainMenuStates::PlayGameButton;
                        menuScreenStates = MenuScreenStates::TitleScreen;
                    }
                } else {
                    backButtonIndex = 0;
                    backButtonColor = {255, 255, 255, 255};
                }

                if (IsGamepadButtonReleased(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) {
                    playButtonColor = { 255, 255, 255, 255 };
                    quitColor = { 255, 255, 255, 255 };
                    creditsColor = { 255, 255, 255, 255 };
                    settingsColor = { 255, 255, 255, 255 };
                    controllerStates = ControllerMainMenuStates::PlayGameButton;
                    menuScreenStates = MenuScreenStates::TitleScreen;
                }

                break;
        }

        

        if (controllerActive) { // Navigating with Controller in Main Menu
            if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_UP)) {
                UpdateByController(ControllerCommands::MOVEUP);
            }
            if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) {
                UpdateByController(ControllerCommands::MOVERIGHT);
            }
            if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) {
                UpdateByController(ControllerCommands::MOVEDOWN);
            }
            if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) {
                UpdateByController(ControllerCommands::MOVELEFT);
            }
        }
    }else{
        --introCounter;
        if(introCounter < 300 && introCounter > 215){
            introFade.a = introFade.a+3;
        }
        if(introCounter < 215 && introCounter >130){
            introFade.a = introFade.a-3;
        }
        if(introCounter < 85){
            introFade.a = introFade.a+3;
        }
        if(introCounter <= 0){
            isIntroDone = true;
        }
    }
  
}

void MainMenu::Draw() {
    Scene::Draw();
    if(isIntroDone) {
        Scene::Draw();
        switch (menuScreenStates) {
            case MenuScreenStates::TitleScreen:
                DrawTexture(mainMenuBackground, 0, 0, WHITE);
                DrawTexture(gameTitlePicture, 450, 60, WHITE);
                DrawTexture(playButton[playButtonIndex], (float) playButtonRec.x, (float) playButtonRec.y,
                            playButtonColor);
                DrawTexture(settingsButton[settingsIndex], (float) settingsButtonRec.x, (float) settingsButtonRec.y,
                            settingsColor);
                DrawTexture(creditsButton[creditsIndex], (float) creditsButtonRec.x, (float) creditsButtonRec.y,
                            creditsColor);
                DrawTexture(quitButton[quitIndex], (float) quitButtonRec.x, (float) quitButtonRec.y, quitColor);

                break;

            case MenuScreenStates::LoadGameScreen:

                DrawTexture(secondaryBackground, 0, 0, WHITE);
                DrawTexture(loadSave1Button[loadSave1Index], loadSave1ButtonRec.x, loadSave1ButtonRec.y,
                            loadSave1Color);
                DrawTexture(loadSave2Button[loadSave2Index], loadSave2ButtonRec.x, loadSave2ButtonRec.y,
                            loadSave2Color);
                DrawTexture(loadSave3Button[loadSave3Index], loadSave3ButtonRec.x, loadSave3ButtonRec.y,
                            loadSave3Color);

                DrawTexture(savegameTex1, 75, 150, WHITE);
                DrawTexture(savegameTex2, 485, 150, WHITE);
                DrawTexture(savegameTex3, 895, 150, WHITE);

                DrawTexture(deleteSave1Button[deleteSave1Index], deleteSave1ButtonRec.x, deleteSave1ButtonRec.y,
                            deleteSave1Color);
                DrawTexture(deleteSave2Button[deleteSave2Index], deleteSave2ButtonRec.x, deleteSave2ButtonRec.y,
                            deleteSave2Color);
                DrawTexture(deleteSave3Button[deleteSave3Index], deleteSave3ButtonRec.x, deleteSave3ButtonRec.y,
                            deleteSave3Color);

                DrawTexture(backButton[backButtonIndex], (float) backButtonRec.x, (float) backButtonRec.y,
                            backButtonColor);
                break;

            case MenuScreenStates::SettingsScreen:

                DrawTexture(secondaryBackground, 0, 0, WHITE);
                if (controllerActive && controllerStates == ControllerMainMenuStates::ChangeMusic) {
                    DrawRectangle(26, 56, 355, 110, ORANGE);
                }
                DrawTexture(musicText, 30, 60, WHITE);
                if (controllerActive && controllerStates == ControllerMainMenuStates::ChangeSound) {
                    DrawRectangle(26, 196, 355, 110, ORANGE);
                }
                DrawTexture(soundText, 30, 200, WHITE);
                if (controllerActive && controllerStates == ControllerMainMenuStates::ChangeFullscreen) {
                    DrawRectangle(26, 336, 355, 110, ORANGE);
                }
                DrawTexture(displayText, 30, 340, WHITE);
                DrawText("0%", musicVolumeRecs[0].x + 10, musicVolumeRecs[0].y + 70, 26, WHITE);
                DrawText("100%", musicVolumeRecs[9].x, musicVolumeRecs[9].y + 70, 26, WHITE);
                DrawText("0%", soundVolumeRecs[0].x + 10, soundVolumeRecs[0].y + 70, 26, WHITE);
                DrawText("100%", soundVolumeRecs[9].x, soundVolumeRecs[9].y + 70, 26, WHITE);
                DrawText("Fullscreen", fullscreenRec.x + 100, fullscreenRec.y + 10, 36, WHITE);

                for (int i = 0; i < 10; i++) { // Drawing Sound and Music Recs in Settings
                    if (isMusicVolumeRecActive[i]) {
                        if (musicVolume == 0 && i == 0) {
                            DrawTexture(redHearth, musicVolumeRecs[i].x, musicVolumeRecs[i].y, WHITE);
                        } else DrawTexture(orangeHearth, musicVolumeRecs[i].x, musicVolumeRecs[i].y, WHITE);
                    } else DrawTexture(emptyHearth, musicVolumeRecs[i].x, musicVolumeRecs[i].y, WHITE);
                    if (isSoundVolumeRecActive[i]) {
                        if (soundVolume == 0 && i == 0) {
                            DrawTexture(redHearth, soundVolumeRecs[i].x, soundVolumeRecs[i].y, WHITE);
                        } else DrawTexture(orangeHearth, soundVolumeRecs[i].x, soundVolumeRecs[i].y, WHITE);
                    } else DrawTexture(emptyHearth, soundVolumeRecs[i].x, soundVolumeRecs[i].y, WHITE);
                }

                if (isFullScreenActive) { // Fullscreen Rec
                    DrawTexture(redHearth, fullscreenRec.x, fullscreenRec.y, WHITE);
                } else DrawTexture(emptyHearth, fullscreenRec.x, fullscreenRec.y, WHITE);

                DrawTexture(backButton[backButtonIndex], (float) backButtonRec.x, (float) backButtonRec.y,
                            backButtonColor);

                break;

            case MenuScreenStates::CreditsScreen: // Drawings Credits

                DrawTexture(secondaryBackground, 0, 0, WHITE);
                DrawText(
                        "Adrian Pfaff - Lead Programmer - Workflows \nAmar Civic - Programmer - Marketing \nRobin Günther - Artist - Animations \nPascal Hirt - Programmer - Sound and Music \nAykan Akgül - Lead Designer - World Design \nAndrea Preussner - Lead Artist - Concept Art",
                        200, 140, 40, WHITE); // I am sorry
                DrawTexture(backButton[backButtonIndex], (float) backButtonRec.x, (float) backButtonRec.y,
                            backButtonColor);

                break;
        }
    }else{
        if(introCounter > 215){
            DrawTexture(introRaylib,0,0,WHITE);
        }else{DrawTexture(introIgnite,0,0,WHITE);}
    }
    DrawRectangleRec(introRec,introFade);
}

MainMenu::~MainMenu()
{
    UnloadTexture(introIgnite);
    UnloadTexture(introRaylib);
    UnloadTexture(mainMenuBackground);
    UnloadTexture(secondaryBackground);
    UnloadTexture(playButton[0]);
    UnloadTexture(playButton[1]);
    UnloadTexture(settingsButton[0]);
    UnloadTexture(settingsButton[1]);
    UnloadTexture(creditsButton[0]);
    UnloadTexture(creditsButton[1]);
    UnloadTexture(quitButton[0]);
    UnloadTexture(quitButton[1]);
    UnloadTexture(gameTitlePicture);
    UnloadTexture(savegameTex1);
    UnloadTexture(savegameTex2);
    UnloadTexture(savegameTex3);
    UnloadTexture(loadSave1Button[0]);
    UnloadTexture(loadSave1Button[1]);
    UnloadTexture(loadSave2Button[0]);
    UnloadTexture(loadSave2Button[1]);
    UnloadTexture(loadSave3Button[0]);
    UnloadTexture(loadSave3Button[1]);
    UnloadTexture(deleteSave1Button[0]);
    UnloadTexture(deleteSave1Button[1]);
    UnloadTexture(deleteSave2Button[0]);
    UnloadTexture(deleteSave2Button[1]);
    UnloadTexture(deleteSave3Button[0]);
    UnloadTexture(deleteSave3Button[1]);
    UnloadTexture(emptyHearth);
    UnloadTexture(redHearth);
    UnloadTexture(orangeHearth);
    UnloadTexture(musicText);
    UnloadTexture(soundText);
    UnloadTexture(displayText);
    UnloadTexture(backButton[0]);
    UnloadTexture(backButton[1]);

    StopMusicStream(track);
    UnloadMusicStream(track);
}

int MainMenu::GetMusicVolume() {
    return musicVolume;
}

int MainMenu::GetSoundVolume() {
    return soundVolume;
}

void MainMenu::SetGameMusicVolume(int volume) {
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
                        soundManager->PlaySfx(SFX::TEST);
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
                        soundManager->PlaySfx(SFX::TEST);
                    }
                    break;
            }
            break;
    }
}

void MainMenu::UpdateMusicAndSoundVolume() {
    for(int i = 0; i<10;i++){ // Activating the Sound and Music Rectangles
        musicVolumeRecs[i] = {(float)(460+(75*i)),80,50,50};
        if(musicVolume>=i){
            isMusicVolumeRecActive[i] = true;
        }else isMusicVolumeRecActive[i] = false;
        if(soundVolume>=i){
            isSoundVolumeRecActive[i] = true;
        }else isSoundVolumeRecActive[i] = false;
        soundVolumeRecs[i] = {(float)(460+(75*i)),220,50,50};
    }

    soundManager->SetSfxVolume(0.2*soundVolume);
    soundManager->SetTrackVolume(0.2*musicVolume);
}

void MainMenu::ResetSave(int slot) {
    std::string saveFolder="./Saves/";
    std::string saveSlot=saveFolder + "save" + "_" + std::to_string(slot) + ".json";
    std::string saveScreen=saveFolder + "save" + "_" + std::to_string(slot) + ".png";
    std::filesystem::copy("./assets/save_reset.json", saveSlot, std::filesystem::copy_options::overwrite_existing);
    std::filesystem::copy("./assets/graphics/savegame/zero.png", saveScreen, std::filesystem::copy_options::overwrite_existing);
    switch (slot) {
        case 1:
        savegameTex1= LoadTexture(saveScreen.c_str());
            break;
        case 2:
            savegameTex2= LoadTexture(saveScreen.c_str());
            break;
        case 3:
            savegameTex3= LoadTexture(saveScreen.c_str());
            break;
        default:
            break;

    }

}
