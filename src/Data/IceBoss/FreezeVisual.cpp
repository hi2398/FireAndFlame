#include "FreezeVisual.h"
#include "../../Global.h"

FreezeVisual::FreezeVisual(Vector2 spawn, int lifetime) : Object(ObjectTypes::other)
{
	position = spawn;
	this->lifetime = lifetime;
	texture = LoadTexture("assets/graphics/OtherObjects/freeze.png");
}

void FreezeVisual::Update()
{
	if (lifetime <= 0) {
		playerCharacter->SetCanMove(true);
		MarkToDestroy();
	}
	else {
		lifetime--;
	}
}

void FreezeVisual::Draw()
{
	DrawTexture(texture, position.x, position.y, WHITE);
}
