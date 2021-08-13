#include "TBJumpUpStage.h"

TBJumpUpStage::TBJumpUpStage(Enemy& enemy) : EState(enemy)
{
}

std::shared_ptr<EState> TBJumpUpStage::Update(Enemy& enemy)
{
	return shared_from_this();
}

void TBJumpUpStage::Draw(Enemy& enemy)
{

}
