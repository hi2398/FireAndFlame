#include "IdleSubState.h"

std::shared_ptr<State> IdleSubState::Update(Actor &actor) {
    return shared_from_this();
}
