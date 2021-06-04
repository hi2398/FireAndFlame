#pragma once
#include "raylib.h"

class Scene {
public:

    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual ~Scene() = default;
protected:

private:

};


