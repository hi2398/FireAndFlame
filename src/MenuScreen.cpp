#include "raylib.h"

#include "MenuScreen.h"
#include "GameScreen.h"
#include "game.h"

Game::MenuScreen::MenuScreen() {
    // Your screen initialization code here...
}

Game::MenuScreen::~MenuScreen() {
    // Your screen cleanup code here...
}


void Game::MenuScreen::ProcessInput() {
    // Your process input code here...
    if (IsKeyPressed(KEY_ENTER)) currentScreen = Game::GameScreen::getInstance();
}

void Game::MenuScreen::Update() {
    // Your update game code here...
}

void Game::MenuScreen::Draw() {
    // Your drawing code here...
    ClearBackground(RAYWHITE);
    DrawText("Menu - press ENTER to start game", 10, 10, 30, LIGHTGRAY);
}
