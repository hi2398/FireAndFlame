#pragma once

#include "Observer/Subject.h"
#include "Actor.h"
#include <iostream>

//#define BUTTON_A 

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


