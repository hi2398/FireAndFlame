#pragma once
#include "../Core/Scene.h"

enum class MenuScreenStates {TitleScreen,LoadGameScreen,SettingsScreen,CreditsScreen};

class MainMenu : public Scene{
public:
    MainMenu();
    void Update() override;
    void Draw() override;
    ~MainMenu() override = default;

protected:

private:

    MenuScreenStates menuScreenStates = {MenuScreenStates::TitleScreen};

    Vector2 vMousePosition;

    //General MenuScreen Background
    Texture2D mainMenuBackground;

    //Title Screen GUI Elements
    Texture2D playButton[3];
    Rectangle playButtonRec;
    int playButtonIndex = 0;

    Texture2D settingsButton[3];
    Rectangle settingsButtonRec;
    int settingsButtonIndex = 0;

    Texture2D creditsButton[3];
    Rectangle creditsButtonRec;
    int creditsButtonIndex = 0;

    Texture2D quitButton[3];
    Rectangle quitButtonRec;
    int quitButtonIndex = 0;

    Texture2D gameTitlePicture;

    //Play Screen
    Rectangle loadSave1ButtonRec;
    Rectangle loadSave2ButtonRec;
    Rectangle loadSave3ButtonRec;
    Rectangle deleteSave1ButtonRec;
    Rectangle deleteSave2ButtonRec;
    Rectangle deleteSave3ButtonRec;
    Rectangle playReturnButtonRec;

    //Settings Screen
        Rectangle musicVolumeRecs[10];
        bool isMusicVolumeRecActive[10];
        int musicVolume;
        Rectangle soundVolumeRecs[10];
        bool isSoundVolumeRecActive[10];
        int soundVolume;
        Rectangle fullscreenRec;
        bool isFullScreenActive = false;

    //Back Button
    Texture2D backButton[3];
    Rectangle backButtonRec;
    int backButtonIndex = 0;

};