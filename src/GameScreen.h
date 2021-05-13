#pragma once

#include <vector>
#include <memory>

#include "raylib.h"

#include "Screen.h"
#include "Sprite.h"

namespace Game {
    class GameScreen : public Screen {
    private:
        std::vector<std::unique_ptr<Sprite>> sprites;

        GameScreen();

    public:
        static Screen *getInstance() {
            static GameScreen instance;
            return &instance;
        }

        GameScreen(GameScreen const &) = delete;

        void operator=(GameScreen const &) = delete;

        ~GameScreen();

        void ProcessInput() override;

        void Update() override;

        void Draw() override;
    };
}
