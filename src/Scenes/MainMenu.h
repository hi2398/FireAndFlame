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
    Texture2D playButton[3];
    Rectangle playButtonRec;
    Texture2D settingsButton[3];
    Rectangle settingsButtonRec;
    Texture2D creditsButton[3];
    Rectangle creditsButtonRec;
    Texture2D quitButton[3];
    Rectangle quitButtonRec;

    Texture2D gameTitlePicture;

    //Play Screen
    Texture2D loadSave1Button[3];
    Rectangle loadSave1ButtonRec;
    Texture2D loadSave2Button[3];
    Rectangle loadSave2ButtonRec;
    Texture2D loadSave3Button[3];
    Rectangle loadSave3ButtonRec;
    Texture2D deleteSave1Button[3];
    Rectangle deleteSave1ButtonRec;
    Texture2D deleteSave2Button[3];
    Rectangle deleteSave2ButtonRec;
    Texture2D deleteSave3Button[3];
    Rectangle deleteSave3ButtonRec;
    Texture2D playReturnButton[3];
    Rectangle playReturnButtonRec;

    //Settings Screen
        //SliderMusic
        //SliderSound
        //Fullscreen
    Texture2D settingsReturnButton[3];

    //Credits Screen
        //Adrian
        //Amar
        //Aykan
        //Mizu
        //Pascal
        //Robin
    Texture2D creditsReturnButton[3];
};