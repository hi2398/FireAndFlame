#include "TBDashState.h"

TBDashState::TBDashState(Enemy& enemy) : EState(enemy)
{
	
}

std::shared_ptr<EState> TBDashState::Update(Enemy& enemy)
{
	return shared_from_this();
}

void TBDashState::Draw(Enemy& enemy)
{

}
