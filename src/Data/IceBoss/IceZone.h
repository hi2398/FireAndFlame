#pragma once

#include "../../Core/Interactable.h"

class IceZone : public Interactable {
public:
    explicit IceZone(Vector2 location);
    void Update() override;
    void Draw() override;
    void Interact(Actor &actor) override;
    ~IceZone() override = default;

protected:


private:
    Texture2D iceZone;
    int lifetime{180};
    const int damageInterval{5}; //60=1s, 5 means it does 12dmg per second
    int damageTimer{0};
};


