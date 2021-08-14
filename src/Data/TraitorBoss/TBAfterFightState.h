#pragma once

#include "../../Core/EState.h"
#include "../../Data/Speechbubble.h"
#include "TraitorBoss.h"
#include <iostream>

class TBAfterFightState : public  EState {

public:
	TBAfterFightState(Enemy& enemy);
	std::shared_ptr<EState> Update(Enemy& enemy) override;
	void Draw(Enemy& enemy) override;
protected:

private:
	Texture2D pseudoTexture{};
	bool endingText{ false };
	int textCounter = 0;
	Vector2 dialogueSpawn;
	Rectangle interactField{};
	int direction;

	std::unique_ptr<Speechbubble> speechbubble;
};