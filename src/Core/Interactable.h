#pragma once
#include "Object.h"

enum class InteractableType{Coal};

class Interactable : public Object {
public:
    explicit Interactable(InteractableType interactableType);
    void Update() override = 0;
    void Draw() override = 0;
    virtual InteractableType GetInteractableType() const;
    virtual void Interact() = 0;
    ~Interactable() override = default;
protected:

private:
    InteractableType interactableType;
};


