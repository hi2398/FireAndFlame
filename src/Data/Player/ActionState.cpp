#include "ActionState.h"

std::shared_ptr<State> ActionState::Update(Actor &actor) {
    return shared_from_this();
}
