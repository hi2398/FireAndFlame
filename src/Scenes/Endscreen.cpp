//
// Created by Ashty on 28.07.2021.
//

#include "Endscreen.h"
#include "../Global.h"
#include "MainMenu.h"
#include <iostream>

Endscreen::Endscreen() {
    endscreenCounter= 0.0f;
    tilemap=std::make_unique<Tilemap>();
    playerCharacter->active = false; // Disables Player
    //TODO Rework
    endText[0] = "FÜR FORTNITE schrie Magmos, als er den Technomancer besiegte";
    endText[1] = "Alle bösen Roboter wurden zerstört, außer die Saugies <3";
    endText[2] = "Und weiterer cooler Story Text!";
    endText[3] = "Habt ihr euch schon das neue Roblox update angeguckt?";
    endText[4] = "THE END?";
    endText[5] = "";
    endText[6] = "Technical Direction: Adrian Pfaff";
    endText[7] = "Programming: Adrian Pfaff";
    endText[8] = "Programming: Amar Civic";
    endText[9] = "Programming: Pascal Hirt";
    endText[10] = "Art Direction: Mizu";
    endText[11] = "Art: Mizu";
    endText[12] = "Art: Robin Günther";
    endText[13] = "Story and Design: Aykan Akgül";
    endText[14] = "Sound and Music: Pascal Hirt";
    endText[15] = "Management: Adrian Pfaff";
    endText[16] = "Marketing: Amar Civic";
}

void Endscreen::Update() {
    endscreenCounter = endscreenCounter + 0.4f;
    if(endscreenCounter >= 1650){
        sceneManager->SetNextScene(std::make_unique<MainMenu>());
    }
}

void Endscreen::Draw() {
    for(int i = 0; i <17;i++){
        const char * c = endText[i].c_str();
        DrawText(c,50,750+(i*50)-endscreenCounter,30,WHITE);
    }
}
