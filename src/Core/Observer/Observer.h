#pragma once

#include "../Actor.h"
#include "Events.h"

class Observer {
public:
    Observer(Actor& actor);
    virtual ~Observer();
    virtual void OnNotify(Event event) = 0;

protected:
    Actor& owner;
private:

};


