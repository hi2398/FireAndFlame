#pragma once
#include "../Core/Scene.h"
#include "../Core/Enemy.h"
#include "../Core/Coal.h"
#include <vector>

class NeutralArea : public Scene {
public:
    NeutralArea();
    void Update() override;
    void Draw() override;
    ~NeutralArea() override = default;

protected:

private:
    int coaltimer=10;
    std::vector<std::shared_ptr<Enemy>> enemies;
    //std::vector<std::shared_ptr<Coal>> coals;
    std::shared_ptr<Coal>coals = std::make_shared<Coal>();
    Rectangle ground = { -1000, 40, 2100, 300};
    int Coaltimer=30;
};

