#include "Foam.h"
#include "raymath.h"

Foam::Foam(Vector2 initialPosition) : Interactable(InteractableType::Foam)
{
	position = initialPosition;
	foamTexture = LoadTexture("assets/graphics/projectiles/Foam.png");

	playerReference = { playerCharacter->GetPosition().x + 16 - position.x, playerCharacter->GetPosition().y + 16 - position.y };
	shootToPlayer = Vector2Normalize(playerReference);
}

void Foam::Update()
{
	interactionZone = { position.x, position.y, (float)foamTexture.width, (float)foamTexture.height };

	position = {position.x + shootToPlayer.x * speed, position.y + shootToPlayer.y * speed};

	if (!CheckCollisionRecs(playerCharacter->visibleScreen, interactionZone)) {
		markedDestroy = true;
	}
}

void Foam::Draw()
{
	DrawTexture(foamTexture, position.x, position.y, WHITE);
}

void Foam::Interact(Actor& actor)
{
	if(CheckCollisionRecs(playerCharacter->playerHitbox, interactionZone)) markedDestroy = true;
	if (!playerCharacter->IsInvulnerable()) playerCharacter->SetInvulnerable(true), playerCharacter->SetHealth(playerCharacter->GetHealth() - 5);
}

Foam::~Foam()
{
	UnloadTexture(foamTexture);
}
