#pragma once
#include <memory>
#include "Tilemap.h"

class Scene {
public:
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual ~Scene() = default;

    const std::unique_ptr<Tilemap>& GetTilemap();
protected:
    std::unique_ptr<Tilemap> tilemap;
private:

};


