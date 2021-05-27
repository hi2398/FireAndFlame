#pragma once
#include "Actor.h"

class Enemy : public Actor {
public:
    Enemy();
    void Draw() override = 0;
    void Update() override = 0;
    ~Enemy() override = default;

protected:

private:

};


