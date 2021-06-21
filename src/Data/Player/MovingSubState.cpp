#include "MovingSubState.h"

std::shared_ptr<State> MovingSubState::Update(Actor &actor) {
    return shared_from_this();
}
