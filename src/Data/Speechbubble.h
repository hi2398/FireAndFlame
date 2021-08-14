#pragma once

#include "../Core/Object.h"


class Speechbubble : public Object {
public:
	Speechbubble(Vector2 initialPos);
	void Update() override;
	void Draw() override;
protected:

private:
	int frameCounter = 0;
	int yOffset = 0;
	Texture2D texture{};
};