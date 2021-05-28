#pragma once
#include "../Core/PlayerCharacter.h"
class IgnitePlayerCharacter : public PlayerCharacter {
public:
    IgnitePlayerCharacter();
    void Draw() override;
    void Update() override;
    ~IgnitePlayerCharacter() override = default;

protected:

private:

};


