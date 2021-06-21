#pragma once
#include <vector>
#include "Object.h"
#include "Component.h"
#include "raylib.h"

class Actor : public Object {
public:
    explicit Actor(ObjectTypes type);
    void Update() override = 0;
    void Draw() override = 0;
    ~Actor() override=default;

protected:
    Vector2 GetLastPosition();
    Vector2 lastTickPos;
private:

};


