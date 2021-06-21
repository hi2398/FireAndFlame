#pragma once
#include <vector>
#include "Object.h"
#include "Component.h"
#include "raylib.h"

enum Direction{LEFT=-1, RIGHT=1};

class Actor : public Object {
public:
    explicit Actor(ObjectTypes type);
    void Update() override = 0;
    void Draw() override = 0;
    ~Actor() override=default;

    void Move(float distance);
    Vector2 GetLastPosition();
    Direction GetDirection() const;

protected:
    Vector2 lastTickPos;
    Direction direction{RIGHT};




private:

};


