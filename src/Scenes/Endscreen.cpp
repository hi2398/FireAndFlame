//
// Created by Ashty on 28.07.2021.
//

#include "Endscreen.h"
#include "../Global.h"
#include "MainMenu.h"
#include <iostream>

Endscreen::Endscreen(SceneEnums lastScene) : Scene(SceneEnums::Default) {
    soundManager->StopThisTrack(false);
    this->lastScene = lastScene;
    endscreenCounter= 0.0f;
    tilemap=std::make_unique<Tilemap>();
    playerCharacter->active = false; // Disables Player

    endText[0] = "After Magmos defeated the Technomancer Maraap";
    endText[1] = "and his Minions he vowed to Rebuild Cremos.";
    endText[2] = "But he wouldn´t be alone on his";
    endText[3] = "Quest of rebuilding his Home.";
    endText[4] = "He got help from the little Roombros";
    endText[5] = "from the Technomancer that were roaming around";
    endText[6] = "without a Task. Now they are helping";
    endText[7] = "to clean up the Planet, while";
    endText[8] = "Magmos is searching for Survivors";
    endText[9] = "to bring back Order to Cremos.";
    endText[10] = "";
    endText[11] = "Design: Aykan Akgül";
    endText[12] = "Art: Andrea Preussner";
    endText[13] = "Art: Robin Günther";
    endText[14] = "Programming: Adrian Pfaff";
    endText[15] = "Programming: Amar Civic";
    endText[16] = "Programming & Sounddesign: Pascal Hirt";

    //music init
    track = LoadMusicStream("assets/audio/tracks/Outro.mp3");
    PlayMusicStream(track);
}

void Endscreen::Update() {
    Scene::Update();
    endscreenCounter = endscreenCounter + 0.4f;
    UpdateMusicStream(track);
    if(endscreenCounter >= 1390){
        StopMusicStream(track);
        sceneManager->SetNextScene(std::make_unique<MainMenu>(sceneName));
    }
}

void Endscreen::Draw() {
    Scene::Draw();
    for(int i = 0; i <17;i++){
        const char * c = endText[i].c_str();
        DrawText(c,150,750+(i*60)-endscreenCounter,38,WHITE);
    }
}

Endscreen::~Endscreen() {
    UnloadMusicStream(track);
}