#pragma once
#include "../Core/Scene.h"

enum class MenuScreenStates {TitleScreen,LoadGameScreen,SettingsScreen,CreditsScreen};

enum class ControllerMainMenuStates {PlayGameButton,SettingsButton,CreditsButton,QuitButton,LoadGame1,LoadGame2,LoadGame3,DeleteGame1,DeleteGame2,DeleteGame3,ChangeMusic,ChangeSound,ChangeFullscreen};

enum class ControllerCommands {MOVERIGHT,MOVELEFT,MOVEUP,MOVEDOWN};

class MainMenu : public Scene{
public:
    MainMenu(SceneEnums lastScene);
    void Update() override;
    void Draw() override;
    ~MainMenu() override;

    int GetMusicVolume();
    int GetSoundVolume();
    bool GetFullscreenActive();
    void SetMusicVolume(int volume);
    void SetSoundVolume(int volume);
    void SetFullscreenActive(bool active);


protected:

private:

    MenuScreenStates menuScreenStates = {MenuScreenStates::TitleScreen};
    ControllerMainMenuStates controllerStates = {ControllerMainMenuStates::PlayGameButton};

    Vector2 vMousePosition;
    bool controllerActive = false;

    void UpdateByController(ControllerCommands controllerCommmand);
    void UpdateMusicAndSoundVolume();

    //General MenuScreen Background
    Texture2D mainMenuBackground;
    Texture2D secondaryBackground;

    //Title Screen GUI Elements
    Texture2D playButton;
    Rectangle playButtonRec;
    Color playButtonColor;

    Texture2D settingsButton;
    Rectangle settingsButtonRec;
    Color settingsColor;

    Texture2D creditsButton;
    Rectangle creditsButtonRec;
    Color creditsColor;

    Texture2D quitButton;
    Rectangle quitButtonRec;
    Color quitColor;

    Texture2D gameTitlePicture;

    //Play Screen
    Texture2D savegameTex1;
    Texture2D savegameTex2;
    Texture2D savegameTex3;

    Texture2D loadSave1Button;
    Rectangle loadSave1ButtonRec;
    Color loadSave1Color;

    Texture2D loadSave2Button;
    Rectangle loadSave2ButtonRec;
    Color loadSave2Color;

    Texture2D loadSave3Button;
    Rectangle loadSave3ButtonRec;
    Color loadSave3Color;

    Texture2D deleteSave1Button[3];
    Rectangle deleteSave1ButtonRec;
    int deleteSave1ButtonIndex = 0;

    Texture2D deleteSave2Button[3];
    Rectangle deleteSave2ButtonRec;
    int deleteSave2ButtonIndex = 0;

    Texture2D deleteSave3Button[3];
    Rectangle deleteSave3ButtonRec;
    int deleteSave3ButtonIndex = 0;


    //Settings Screen
    Rectangle musicVolumeRecs[10];
    Texture2D emptyHearth;
    Texture2D redHearth;
    Texture2D orangeHearth;

    Texture2D musicText;
    Texture2D soundText;
    Texture2D displayText;

    bool isMusicVolumeRecActive[10];
    int musicVolume = 5;
    Rectangle soundVolumeRecs[10];
    bool isSoundVolumeRecActive[10];
    int soundVolume = 5;
    Rectangle fullscreenRec;
    bool isFullScreenActive = false;

    //Back Button
    Texture2D backButton;
    Color backButtonColor = {255,255,255,255};
    Rectangle backButtonRec;
};