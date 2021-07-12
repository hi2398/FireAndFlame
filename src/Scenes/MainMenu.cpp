#include "MainMenu.h"
#include "../Global.h"
#include <iostream>
#define RAYGUI_IMPLEMENTATION
#include "../raygui.h"

MainMenu::MainMenu() {
    tilemap=std::make_unique<Tilemap>();
    playerCharacter->visible = false;
}

void MainMenu::Update() {

}

void MainMenu::Draw() {

}