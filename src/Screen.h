#pragma once

namespace Game {
    class Screen {
    public:
        virtual ~Screen() = default;

        virtual void ProcessInput() = 0;

        virtual void Update() = 0;

        virtual void Draw() = 0;
    };
}
