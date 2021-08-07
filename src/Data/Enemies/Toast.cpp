#include "Toast.h"
#include <cmath>
#include "../../Global.h"

Toast::Toast(Vector2 initialPosition) : Interactable(InteractableType::Toast)
{
	position = initialPosition;
	if (GetRandomValue(0, 19) == 0) {
		toastTexture = LoadTexture("assets/graphics/Enemies/Burned_Toast.png");
		ToastIsBurned = true;
	}
	else {
		toastTexture = LoadTexture("assets/graphics/Enemies/Toast.png");
		ToastIsBurned = false;
	}

	yDiff = position.y - playerCharacter->GetPosition().y;
	xDiff = playerCharacter->GetPosition().x - position.x;
	if (xDiff < 0) revert = -1.0f;

	if (yDiff < 0) {
		attackDirection = 0.7 *(abs(xDiff) - ((pow(yDiff, 2) / pow(abs(xDiff), 2)))) / (abs(xDiff)) * abs(xDiff) / (float)(32 * 4);
	}
	else if (yDiff > 0) {
		attackDirection = (((pow(yDiff, 2) / pow(abs(xDiff), 2))) + abs(xDiff)) / (abs(xDiff)) * abs(xDiff) /(float)(32 * 4);
	}
	else {
		attackDirection = abs(xDiff) / (32 * 5);
	}
	std::cout << attackDirection << "\n";
}

void Toast::Update()
{
	//hitbox update
	interactionZone = {position.x, position.y, (float)toastTexture.width, (float)toastTexture.height};

	//flight curve
	position.y -= toastSpeed;
	toastSpeed -= toastGravity;
	position.x += toastDistance * attackDirection * revert;

	existenceCounter++;
	if (existenceCounter >= 300 && (!CheckCollisionRecs(playerCharacter->visibleScreen, interactionZone) || CheckCollisionRecs(playerCharacter->playerHitbox, interactionZone))) {
		markedDestroy = true;
	}
}

void Toast::Draw()
{
	DrawTexture(toastTexture, position.x, position.y, WHITE);
}

void Toast::Interact(Actor& actor)
{
	if (ToastIsBurned) {
		if (!playerCharacter->IsInvulnerable()) playerCharacter->SetInvulnerable(true), playerCharacter->SetHealth(playerCharacter->GetHealth() - 10);
	}
	else {
		if (!playerCharacter->IsInvulnerable()) playerCharacter->SetInvulnerable(true), playerCharacter->SetHealth(playerCharacter->GetHealth() - 5);
	}
	
}
