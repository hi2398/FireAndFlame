#pragma once
#include "Actor.h"

class PlayerCharacter : public Actor {
public:
    PlayerCharacter();
    void Draw() override = 0;
    void Update() override = 0;
    ~PlayerCharacter() override = default;

protected:

private:

};


