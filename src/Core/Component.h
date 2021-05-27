#pragma once
#include "Object.h"

class Component {
public:
    explicit Component(std::weak_ptr<Object> owner);
    virtual void Update() = 0;
    virtual ~Component() = default;
protected:

private:
    std::weak_ptr<Object> owner;
};


