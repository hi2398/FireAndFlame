#include "Speechbubble.h"
#include "../Global.h"

Speechbubble::Speechbubble(Vector2 initialPos) : Object(ObjectTypes::other)
{
	position.x = initialPos.x - 8;
	position.y = initialPos.y - 5;
	
	texture = LoadTexture("assets/graphics/OtherObjects/Speechbubble.png");
}

void Speechbubble::Update()
{
	frameCounter++;
	if (frameCounter >= 45) {
		if (yOffset == 0) yOffset = 2;
		else yOffset = 0;
		frameCounter = 0;
	}
}

void Speechbubble::Draw()
{
	if (!playerCharacter->InputDisabled()) DrawTexture(texture, position.x, position.y + yOffset, WHITE);
}

Speechbubble::~Speechbubble()
{
	UnloadTexture(texture);
}
