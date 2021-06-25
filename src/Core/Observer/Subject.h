#pragma once

#include <list>
#include "Observer.h"

class Subject {
public:
    void AddObserver(Observer &observer);

    void RemoveObserver(Observer &observer);

protected:
    void Notify(EVENT event);

private:
    std::list<Observer*> observers;
};


