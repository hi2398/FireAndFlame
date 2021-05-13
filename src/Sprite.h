#pragma once

#include "raylib.h"

namespace Game {
    struct Sprite {
        Vector2 pos = {0.0f, 0.0f};
        Texture2D texture {};
        bool visible = true;

        Sprite() = default;

        explicit Sprite(Texture2D texture) : texture(texture) {}

        Sprite(Texture2D texture, Vector2 pos, bool visible) : texture(texture), pos(pos), visible(visible) {}

        Sprite(Sprite &&other)  noexcept : texture(other.texture), pos(other.pos), visible(other.visible) {}

        ~Sprite() = default;

        Sprite& operator=(const Sprite& other) = default;
    };
}
