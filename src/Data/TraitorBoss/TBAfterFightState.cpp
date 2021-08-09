#include "TBAfterFightState.h"

TBAfterFightState::TBAfterFightState(Enemy& enemy) : EState(enemy)
{

}

std::shared_ptr<EState> TBAfterFightState::Update(Enemy& enemy)
{
	return shared_from_this();
}

void TBAfterFightState::Draw(Enemy& enemy)
{

}
