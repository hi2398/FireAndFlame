#include <memory>
#include "MainMenu.h"
#include "raylib.h"
#include "NeutralArea.cpp"
#include "../Global.h"

void MainMenu::Update() {
    sceneManager->SetNextScene(std::make_unique<NeutralArea>());

}

void MainMenu::Draw() {

}