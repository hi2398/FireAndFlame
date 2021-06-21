#include "MovementState.h"

std::shared_ptr<State> MovementState::Update(Actor &actor) {
    return shared_from_this();
}
