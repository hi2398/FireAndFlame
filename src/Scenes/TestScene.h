#pragma once
#include "../Core/Scene.h"
#include <vector>
#include "../Core/Tilemap.h"

class TestScene : public Scene {
public:
    TestScene();
    void Update() override;
    void Draw() override;
    ~TestScene() override = default;

protected:

private:
    std::unique_ptr<Tilemap> tilemap;
};



