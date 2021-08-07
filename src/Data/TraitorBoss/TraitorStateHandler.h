#pragma once

#include "../../Core/EState.h"

class TraitorStateHandler : public EState {
public:
	TraitorStateHandler(Enemy &enemy);
	std::shared_ptr<EState> Update(Enemy& enemy) override;
	void Draw(Enemy& enemy) override;
protected:

private:

};