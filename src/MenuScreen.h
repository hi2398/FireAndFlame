#pragma once

#include "Screen.h"

namespace Game {
    class MenuScreen : public Screen {
    private:
        MenuScreen();

    public:
        static Screen * getInstance() {
            static MenuScreen instance;
            return &instance;
        }

        MenuScreen(MenuScreen const &) = delete;

        void operator=(MenuScreen const &) = delete;

        ~MenuScreen();

        void ProcessInput() override;

        void Update() override;

        void Draw() override;
    };
}
