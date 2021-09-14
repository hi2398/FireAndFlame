#include "Door.h"

Door::Door(Vector2 position, bool isOpen) : Object(ObjectTypes::other)
{
	this->isOpen = isOpen;
	this->position = position;
	this->texture = LoadTexture("assets/graphics/OtherObjects/environment.png");
}

void Door::Update()
{
	if (isOpen)  activeFrame.x = 9 * 32;
	else activeFrame.x = 8 * 32;
}

void Door::Draw()
{
	DrawTextureRec(texture, activeFrame, position, WHITE);
}

void Door::SetIsOpen(bool isOpen)
{
	this->isOpen = isOpen;
}

Door::~Door()
{
	UnloadTexture(texture);
}
