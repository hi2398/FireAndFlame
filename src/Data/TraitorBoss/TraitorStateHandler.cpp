#include "TraitorStateHandler.h"
#include "TBAfterFightState.h"
#include "TBBeforeFightState.h"

TraitorStateHandler::TraitorStateHandler(Enemy& enemy) : EState(enemy)
{
	activeState = std::make_shared<TBBeforeFightState>(enemy);
}

std::shared_ptr<EState> TraitorStateHandler::Update(Enemy& enemy)
{
	if (enemy.GetHealth() <= 0) activeState = std::make_shared<TBAfterFightState>(enemy);
	else if (enemy.GetHealth() == 100) activeState = std::make_shared<TBBeforeFightState>(enemy);


	activeState = activeState->Update(enemy);
	return shared_from_this();
}

void TraitorStateHandler::Draw(Enemy& enemy)
{

}
