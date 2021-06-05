#pragma once
#include "Object.h"

class Interactable : public Object {
public:
    Interactable();
    void Update() override = 0;
    void Draw() override = 0;
    virtual void Interact() = 0;
    ~Interactable() override = default;
protected:

private:

};


