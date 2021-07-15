#pragma once
#include "../Core/Scene.h"

class DeathScreen : public Scene {
public:
    DeathScreen();
    void Update() override;
    void Draw() override;
    ~DeathScreen() override = default;

private:

protected:

};
