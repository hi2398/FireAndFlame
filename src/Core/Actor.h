#pragma once
#include <vector>
#include "Object.h"
#include "Component.h"

class Actor : public Object {
public:
    explicit Actor(ObjectTypes type);
    void Update() override = 0;
    void Draw() override = 0;

    template<class T>
    std::unique_ptr<Component> AddComponent();
    ~Actor() override=default;

protected:

private:
    std::vector<Component> components;
};


