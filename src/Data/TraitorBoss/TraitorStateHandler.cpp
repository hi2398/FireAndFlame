#include "TraitorStateHandler.h"
#include "TBAfterFightState.h"

TraitorStateHandler::TraitorStateHandler(Enemy& enemy) : EState(enemy)
{

}

std::shared_ptr<EState> TraitorStateHandler::Update(Enemy& enemy)
{
	if (enemy.GetHealth() >= 0) return std::make_shared<TBAfterFightState>(enemy);


	return shared_from_this();
}

void TraitorStateHandler::Draw(Enemy& enemy)
{
}
