#pragma once
#include "Actor.h"

class PlayerCharacter : public Actor {
public:
    PlayerCharacter();
    void Draw() override;
    void Update() override;
    ~PlayerCharacter() override = default;

protected:

private:

};


