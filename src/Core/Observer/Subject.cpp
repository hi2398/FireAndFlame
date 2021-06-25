#include <algorithm>
#include "Subject.h"

void Subject::AddObserver(Observer& observer) {
    observers.push_back(&observer);
}

void Subject::RemoveObserver(Observer& observer) {
    observers.erase(std::find(observers.begin(), observers.end(), &observer));
}

void Subject::Notify(EVENT event) {
    for(const auto &x : observers){
        x->OnNotify(event);
    }
}
