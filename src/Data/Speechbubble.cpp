#include "Speechbubble.h"

Speechbubble::Speechbubble(Vector2 initialPos) : Object(ObjectTypes::other)
{
	position.x = initialPos.x - 8;
	position.y = initialPos.y - 5;
	
	texture = LoadTexture("assets/graphics/OtherObjects/Speechbubble.png");
}

void Speechbubble::Update()
{
	frameCounter++;
	if (frameCounter >= 15) {
		if (yOffset == 0) yOffset = 3;
		else yOffset = 0;
		frameCounter = 0;
	}
}

void Speechbubble::Draw()
{
	DrawTexture(texture, position.x, position.y + yOffset, WHITE);
}