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


};


