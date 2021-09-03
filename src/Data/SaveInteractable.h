#pragma once

#include "../Core/Interactable.h"

class SaveInteractable : public Interactable {
public:

    explicit SaveInteractable(Vector2 pos);

    void Update() override;

    void Draw() override;

    void Interact(Actor &actor) override;

    ~SaveInteractable() override = default;

protected:


private:
    int saveCooldown{0};
    const int cooldown{7200}; //2min cooldown=7200
    Texture2D lampOn;
    Texture2D lampOff;
};


