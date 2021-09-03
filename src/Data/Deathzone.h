#pragma once
#include "raylib.h"
#include "../Global.h"
#include "../Core/Interactable.h"

class Deathzone : public Interactable{
public:
    Deathzone(Vector2 location={0, 0});
    void Interact(Actor& actor)override;
    Rectangle GetHitbox();
    void Update() override;
    void Draw() override;
    ~Deathzone() override;

private:

protected:
};
