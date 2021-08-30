#include "HitMarker.h"
#include <iostream>

HitMarker::HitMarker(Vector2 initialPos) : Interactable(InteractableType::Other)
{
	texture = LoadTexture("assets/graphics/hit_explosion.png");
	position = initialPos;
	activeFrame = {0,0,16,16};
}

void HitMarker::Update()
{
	frameCounter++;
	if (frameCounter % 5 == 0) {
		thisFrame++;
	}
	if (frameCounter >= 14) MarkToDestroy();

	activeFrame = { (float)thisFrame * 16, 0, 16, 16 };

}

void HitMarker::Draw()
{
	DrawTexturePro(texture, activeFrame, {position.x, position.y, 32, 32}, {0,0}, 0.0, WHITE);
}
