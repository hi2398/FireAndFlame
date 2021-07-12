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

    //General MenuScreen Background
    Texture2D mainMenuBackground;

    //Title Screen GUI Elements
    Rectangle playButton;
    Rectangle settingsButton;
    Rectangle creditsButton;
    Rectangle quitButton;

    Texture2D gameTitlePicture;

    //Play Screen
    Rectangle loadSave1Button;
    Rectangle loadSave2Button;
    Rectangle loadSave3Button;
    Rectangle deleteSave1Button;
    Rectangle deleteSave2Button;
    Rectangle deleteSave3Button;
    Rectangle playReturnButton;

    //Settings Screen
        //SliderMusic
        //SliderSound
        //Fullscreen
    Rectangle settingsReturnButton;

    //Credits Screen
        //Adrian
        //Amar
        //Aykan
        //Mizu
        //Pascal
        //Robin
    Rectangle creditsReturnButton;
};