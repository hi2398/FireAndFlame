#pragma once
#include "Object.h"
#include "Actor.h"

enum class InteractableType{Coal,SceneChangeCollider,DialogObj, IceZone, FinalBossAttack, Toast, Foam, Fireball};

class Interactable : public Object {
public:
    explicit Interactable(InteractableType interactableType);
    void Update() override = 0;
    void Draw() override = 0;
    virtual InteractableType GetInteractableType() const;
    [[nodiscard]] Rectangle GetInteractionZone() const;
    virtual void Interact(Actor& actor) = 0;

    ~Interactable() override = default;


protected:
    Rectangle interactionZone{};

private:
    InteractableType interactableType;
};