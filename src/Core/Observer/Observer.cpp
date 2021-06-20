#include "Observer.h"

Observer::Observer(Actor& actor) : owner(actor) {

}

Observer::~Observer() = default;
