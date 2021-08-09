#include "TBBeforeFightState.h"

TBBeforeFightState::TBBeforeFightState(Enemy& enemy) : EState(enemy)
{

}

std::shared_ptr<EState> TBBeforeFightState::Update(Enemy& enemy)
{

	return shared_from_this();
}

void TBBeforeFightState::Draw(Enemy& enemy)
{

}
