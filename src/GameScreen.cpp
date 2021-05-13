#include "raylib.h"

#include "GameScreen.h"
#include "MenuScreen.h"
#include "game.h"

Game::GameScreen::GameScreen() {
    // Your screen initialization code here...
    Vector2 vec = {100.0f, 100.0f};
    this->sprites.push_back(
            std::make_unique<Game::Sprite>(LoadTexture("assets/graphics/testimage.png"),
                                           vec,
                                           true)
    );
}

Game::GameScreen::~GameScreen() {
    // Your screen cleanup code here...
    UnloadTexture(sprites[0]->texture);
}

void Game::GameScreen::ProcessInput() {
    // Your process input code here...
    if (IsKeyPressed(KEY_ENTER)) currentScreen = Game::MenuScreen::getInstance();
}

void Game::GameScreen::Update() {
    // Your update game code here...
}

void Game::GameScreen::Draw() {
    // Your drawing code here...
    ClearBackground(RAYWHITE);
    DrawText("Game - press ENTER for menu", 10, 10, 30, LIGHTGRAY);

    for (const auto &sprite : this->sprites) {
        if (sprite->visible)
            DrawTexture(sprite->texture, (int) sprite->pos.x, (int) sprite->pos.y, RAYWHITE);
    }
}
