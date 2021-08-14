#include "HeartObject.h"

HeartObject::HeartObject(Vector2 initialPos, HeartState heartState, int lifetime) : Object(ObjectTypes::other)
{
	position.x = initialPos.x + 10;
	position.y = initialPos.y - 12;
	this->heartState = heartState;
	this->lifetime = lifetime;
	switch (heartState)
	{
	case HeartState::Good:
		texture = LoadTexture("assets/graphics/OtherObjects/Heart.png");
		break;
	case HeartState::Bad:
		texture = LoadTexture("assets/graphics/OtherObjects/Broken_Heart.png");
		break;
	default:
		break;
	}
}

void HeartObject::Update()
{
	frameCounter++;
	if (frameCounter >= 15) {
		if (yOffset == 0) yOffset = 3;
		else yOffset = 0;
		frameCounter = 0;
		lifetime--;
	}

	if (lifetime <= 0) {
		markedDestroy = true;
	}
}

void HeartObject::UpdatePos(Vector2 updatedPos)
{
	position.x = updatedPos.x + 10;
	position.y = updatedPos.y - 12;
}

void HeartObject::Draw()
{
	DrawTexture(texture, position.x, position.y + yOffset, WHITE);
}
