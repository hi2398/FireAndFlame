#include "Fly.h"
#include "../../Global.h"
#include "EnemyStateHandler.h"


Fly::Fly(Vector2 initialPos) : Enemy(EnemyTypes::Flyer)
{
	texture = LoadTexture("assets/graphics/Enemies/Fliege_01_Spritesheet.png");

	position.x = initialPos.x;
	position.y = initialPos.y;

	activeState = std::make_shared<EnemyStateHandler>(*this);

	movementSpeed = 0.5f;
}

void Fly::Update()
{
	activeState = activeState->Update(*this);

	UpdateCollider(0, 20, 32, 12);

	if (invulnerable) {
		invulnerableCounter++;
		if (invulnerableCounter >= 60) {
			invulnerableCounter = 0;
			invulnerable = false;
		}
	}

	
	CollisionLeft(sceneManager->GetTilemap());
	CollisionRight(sceneManager->GetTilemap());
	CollisionGround(sceneManager->GetTilemap());
	CollisionHead(sceneManager->GetTilemap());
}

void Fly::Draw()
{
	activeState->Draw(*this);
	DrawText(TextFormat("%i", health), position.x, position.y - 50, 30, WHITE);
}
