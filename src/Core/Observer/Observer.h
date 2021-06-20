#pragma once

#include "../Actor.h"
#include "Events.h"

class Observer {
public:
    Observer();
    virtual ~Observer();
    virtual void OnNotify(const Actor& actor, Event event) = 0;

protected:

private:

};


