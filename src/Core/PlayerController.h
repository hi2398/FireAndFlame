#pragma once

#include "Observer/Subject.h"

class PlayerController : public Subject {
public:
    PlayerController();
    void HandleInput();
    ~PlayerController();
 
protected:

private:
    const int right = 1;
    const int left = -1;

};


