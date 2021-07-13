#include "MainMenu.h"
#include "../Global.h"
#include <iostream>

MainMenu::MainMenu() {
    tilemap=std::make_unique<Tilemap>();
    playerCharacter->visible = false;
}

void MainMenu::Update() {

}

void MainMenu::Draw() {

}